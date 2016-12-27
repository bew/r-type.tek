/**
 * @file JsonParser.cpp
 * @brief Class for JsonParser
 * @author Christopher Paccard
 *
 * Allow to parse JSON to BSON
 *
 */

#include "JsonParser.hh"

namespace bson {
    JsonParser::JsonParser(const std::string &json) : _json(json), _pos(_json.begin()) {}

    JsonParser::~JsonParser() {}

    bson::Document JsonParser::parse() {
        bson::Document document;

        this->ignoreBlanks();
        if (_pos == _json.end())
            return document;

        this->ignoreBlanks();
        if (!this->readObject(document) && !this->readArray(document))
            throw BsonException(this->getErrorMessage(std::string("can't parse object or array")));

        this->ignoreBlanks();
        if (_pos != _json.end())
            throw BsonException(std::string("more than one root object or array"));

        return document;
    }

    std::string JsonParser::getErrorMessage(const std::string &string) const {
        return std::string("Invalid JSON: ") + string + std::string(", at position: ") +
               std::to_string(_pos - _json.begin()) + std::string(" (") + *_pos + std::string(")");
    }

    bool JsonParser::beginCapture(const std::string &tag) {
        if (_pos == _json.end())
            return false;
        _tags[tag] = _pos;
        return true;
    }

    bool JsonParser::endCapture(const std::string &tag, std::string &out) {
        if (!_tags.count(tag))
            return false;
        out.insert(out.begin(), _tags.at(tag), _pos);
        return true;
    }

    bool JsonParser::peekChar(char c) const {
        return _pos != _json.end() && *_pos == c;
    }

    bool JsonParser::readChar(char c) {
        if (_pos != _json.end() && this->peekChar(c)) {
            ++_pos;
            return true;
        } else
            return false;
    }

    bool JsonParser::readDigit() {
        static const char digits[11] = "0123456789";

        size_t i = 0;
        while (digits[i]) {
            if (this->readChar(digits[i]))
                return true;
            else
                ++i;
        }
        return false;
    }

    bool JsonParser::readUntil(char c) {
        SAVE_CONTEXT;
        while (_pos != _json.end()) {
            if (*_pos == c)
                return true;
            else
                ++_pos;
        }
        RESTORE_CONTEXT;
        return false;
    }

    bool JsonParser::readText(const std::string &string) {
        if (_pos == _json.end())
            return false;

        SAVE_CONTEXT;
        for (const auto &it : string) {
            if (!this->readChar(it)) {
                RESTORE_CONTEXT;
                return false;
            }
        }

        return true;
    }

    void JsonParser::ignoreBlanks() {
        while (_pos != _json.end() && (*_pos == ' ' || *_pos == '\t' || *_pos == '\n'))
            ++_pos;
    }

    bool JsonParser::readDouble(bson::Document &document) {
        SAVE_CONTEXT;
        bool negative = this->readChar('-');

        if (!this->beginCapture("readDoubleTag") || !this->readDigit()) {
            RESTORE_CONTEXT;
            return false;
        }

        while (this->readDigit());

        if (!this->readChar('.')) {
            RESTORE_CONTEXT;
            return false;
        }

        std::string number;
        this->endCapture("readDoubleTag", number);
        double floating = std::stod(number);

        if (negative)
            floating *= -1;

        document << floating;

        return true;
    }

    bool JsonParser::readString(bson::Document &document) {
        if (!this->readChar('"'))
            return false;

        SAVE_CONTEXT;
        if (!this->beginCapture("readStringTag") || !this->readUntil('"')) {
            RESTORE_CONTEXT;
            throw BsonException(this->getErrorMessage(std::string("can't end the string")));
        }

        std::string string;
        this->endCapture("readStringTag", string);
        document << string;

        this->readChar('"');

        return true;
    }

    bool JsonParser::readObject(bson::Document &document) {
        SAVE_CONTEXT;
        if (!this->readChar('{')) {
            RESTORE_CONTEXT;
            return false;
        }

        bool first = true;
        this->ignoreBlanks();
        while (!this->readChar('}')) {
            if (!first && !this->readChar(','))
                throw BsonException(this->getErrorMessage("missing ','"));

            this->ignoreBlanks();
            if (!this->readString(document))
                throw BsonException(this->getErrorMessage("can't find any key"));

            this->ignoreBlanks();
            if (!this->readChar(':'))
                throw BsonException(this->getErrorMessage("can't parse pair, got: ") + *_pos);

            bson::Document innerDocument;
            this->ignoreBlanks();
            if (!this->readDouble(document) &&
                !this->readString(document) &&
                !this->readObject(innerDocument) &&
                !this->readArray(innerDocument) &&
                !this->readBool(document) &&
                !this->readNull(document) &&
                !this->readInteger(document))
                throw BsonException(this->getErrorMessage("no value detected"));
            if (!innerDocument.isEmpty())
                document << innerDocument;

            first = false;
            this->ignoreBlanks();
        }

        return true;
    }

    bool JsonParser::readArray(bson::Document &document) {
        SAVE_CONTEXT;
        if (!this->readChar('[')) {
            RESTORE_CONTEXT;
            return false;
        }

        document << bson::Document::ARRAY_ENABLED;
        bool first = true;
        this->ignoreBlanks();
        while (!this->readChar(']')) {
            if (!first && !this->readChar(','))
                throw BsonException(this->getErrorMessage("missing ','"));

            bson::Document innerDocument;
            this->ignoreBlanks();
            if (!this->readDouble(document) &&
                !this->readString(document) &&
                !this->readObject(innerDocument) &&
                !this->readArray(innerDocument) &&
                !this->readBool(document) &&
                !this->readNull(document) &&
                !this->readInteger(document))
                throw BsonException(this->getErrorMessage("no value detected"));
            if (!innerDocument.isEmpty())
                document << innerDocument;

            first = false;
            this->ignoreBlanks();
        }
        document << bson::Document::ARRAY_DISABLED;

        return true;
    }

    bool JsonParser::readBool(bson::Document &document) {
        if (this->readText("true")) {
            document << true;
            return true;
        } else if (this->readText("false")) {
            document << false;
            return true;
        } else
            return false;
    }

    bool JsonParser::readNull(bson::Document &document) {
        if (this->readText("null")) {
            document << nullptr;
            return true;
        } else
            return false;
    }

    bool JsonParser::readInteger(bson::Document &document) {
        SAVE_CONTEXT;
        bool negative = this->readChar('-');

        if (!this->beginCapture("readIntegerTag") || !this->readDigit()) {
            RESTORE_CONTEXT;
            return false;
        }

        while (this->readDigit());

        std::string number;
        this->endCapture("readIntegerTag", number);
        int64_t integer = std::stoll(number);

        if (negative)
            integer *= -1;

        if (-2147483648 <= integer && integer <= 21747483647)
            document << static_cast<int32_t>(integer);
        else
            document << integer;

        return true;
    }
}