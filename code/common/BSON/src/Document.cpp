/**
 * @file Document.cpp
 * @brief Class for BSON document
 * @author Christopher Paccard
 *
 * Represent a BSON document
 *
 */

#include "Document.hh"
#include "Endianess.hh"

namespace bson {
    Document::Document() :_nextInputType(bson::Document::KEY) {
    }

    Document::Document(const Document &document) {
        if (this != &document) {
            _nextInputType = document._nextInputType;
            _lastKey = document._lastKey;
            _buffer = document._buffer;
        }
    }

    Document& Document::operator=(const Document &document) {
        if (this != &document) {
            _nextInputType = document._nextInputType;
            _lastKey = document._lastKey;
            _buffer = document._buffer;
        }
        return *this;
    }

    Document::~Document() {
    }

    void Document::isInputValue() const {
        if (_nextInputType != Document::VALUE)
            throw std::runtime_error("Next input into the document should be a key as a string.");
    }

    void Document::writeTypeCodeAndKey(unsigned char typeCode) {
        _buffer.push_back(typeCode);
        for (int i = 0; _lastKey[i]; ++i)
            _buffer.push_back((unsigned char &&) static_cast<unsigned char>(_lastKey[i]));
        _buffer.push_back('\x00');
    }

    std::vector<unsigned char> Document::getBuffer() const {
        std::vector<unsigned char> entireBuffer;

        union {
            int32_t integer;
            unsigned char bytes[4];
        } cutInteger;
        cutInteger.integer = (CHOOSE_ENDIANESS_32(_buffer.size() + 5));

        for (const auto &byte : cutInteger.bytes)
            entireBuffer.push_back(byte);
        for (const auto &byte : _buffer)
            entireBuffer.push_back(byte);
        entireBuffer.push_back('\x00');

        return entireBuffer;
    }

    Document &Document::operator<<(const char *string) {
        if (_nextInputType != KEY)
            throw std::runtime_error("A C string can only be used as a key.");

        std::string key(string);
        if (!key.size())
            throw std::runtime_error("A key can't be empty.");

        _lastKey = key;
        _nextInputType = VALUE;
        return *this;
    }

    Document& Document::operator<<(double floating) {
        this->isInputValue();

        union {
            double floating;
            unsigned char bytes[8];
        } cutFloating;
        cutFloating.floating = CHOOSE_ENDIANESS_64(floating);
        type valueType = DOUBLE;

        this->writeTypeCodeAndKey(typesCodes.at(valueType));
        for (const auto &byte : cutFloating.bytes)
            _buffer.push_back(byte);

        _nextInputType = KEY;

        return *this;
    }

    Document &Document::operator<<(const std::string &string) {
        if (_nextInputType == KEY)
            *this << string.c_str();
        else {
            union {
                int32_t integer;
                unsigned char bytes[4];
            } cutInteger;
            cutInteger.integer = (CHOOSE_ENDIANESS_32(string.length() + 1));
            type valueType = STRING;

            this->writeTypeCodeAndKey(typesCodes.at(valueType));
            for (const auto &byte : cutInteger.bytes)
                _buffer.push_back(byte);
            for (const auto &character : string)
                _buffer.push_back((unsigned char &&) static_cast<unsigned char>(character));
            _buffer.push_back('\x00');

            _nextInputType = KEY;
        }

        return *this;
    }

    Document &Document::operator<<(const Document &document) {
        this->isInputValue();

        const std::vector<unsigned char> &buffer = document.getBuffer();

        type valueType = DOCUMENT;

        this->writeTypeCodeAndKey(typesCodes.at(valueType));
        for (const auto &byte : buffer)
            _buffer.push_back(byte);

        _nextInputType = KEY;
        return *this;
    }

    Document &Document::operator<<(bool boolean) {
        this->isInputValue();

        type valueType = BOOL;

        this->writeTypeCodeAndKey(typesCodes.at(valueType));
        _buffer.push_back((unsigned char &&) static_cast<unsigned char>(boolean));

        _nextInputType = KEY;
        return *this;
    }

    Document &Document::operator<<(std::nullptr_t __attribute__((unused)) ptr) {
        this->isInputValue();

        type valueType = NULLVALUE;

        this->writeTypeCodeAndKey(typesCodes.at(valueType));

        _nextInputType = KEY;
        return *this;
    }

    Document &Document::operator<<(int32_t integer)
    {
        this->isInputValue();

        union {
            int32_t integer;
            unsigned char bytes[4];
        } cutInteger;
        cutInteger.integer = (CHOOSE_ENDIANESS_32(integer));
        type valueType = INT32;

        this->writeTypeCodeAndKey(typesCodes.at(valueType));
        for (const auto &byte : cutInteger.bytes)
            _buffer.push_back(byte);

        _nextInputType = KEY;
        return *this;
    }

    Document &Document::operator<<(int64_t integer)
    {
        this->isInputValue();

        union {
            int64_t integer;
            unsigned char bytes[8];
        } cutInteger;
        cutInteger.integer = (CHOOSE_ENDIANESS_64(integer));
        type valueType = INT64;

        this->writeTypeCodeAndKey(typesCodes.at(valueType));
        for (const auto &byte : cutInteger.bytes)
            _buffer.push_back(byte);

        _nextInputType = KEY;
        return *this;
    }
}