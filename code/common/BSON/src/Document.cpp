/**
 * @file Document.cpp
 * @brief Class for BSON document
 * @author Christopher Paccard
 *
 * Represent a BSON document
 *
 */

#include <iostream>
#include "Document.hh"
#include "Endianess.hh"

namespace bson {

    Document::Element::Element(type valueType, const std::string &key, const std::vector<unsigned char> &value)
    : _valueType(valueType), _key(key), _value(value)  {
    }

    Document::Element::Element(const Document::Element &element) {
        this->operator=(element);
    }

    Document::Element& Document::Element::operator=(const Document::Element &element) {
        if (this != &element) {
            _valueType = element._valueType;
            _key = element._key;
            _value = element._value;
        }
        return *this;
    }

    Document::Element::~Element() {
    }

    void Document::Element::isRightType(bson::type valueType) const {
        if (valueType != _valueType)
            throw BsonException("The value store inside the element is not the same as requested.");
    }

    bson::type Document::Element::getValueType() const {
        return _valueType;
    }

    const std::string& Document::Element::getKey() const {
        return _key;
    }

    double Document::Element::getValueDouble() const {
        this->isRightType(bson::DOUBLE);

        union {
            double floating;
            unsigned char bytes[8];
        } cutFloating;

        for (size_t i = 0; i < 8; ++i)
            cutFloating.bytes[i] = _value[i];

        return (IS_BIG_ENDIAN ? swap_endian<double>(cutFloating.floating) : cutFloating.floating);
    }

    void Document::Element::getValue(double &floating) const {
        floating = this->getValueDouble();
    }

    std::string Document::Element::getValueString() const {
        this->isRightType(bson::STRING);

        return std::string(_value.begin() + 4, _value.end() - 1);
    }

    void Document::Element::getValue(std::string &string) const {
        string = this->getValueString();
    }

    Document Document::Element::getValueDocument() const {
        this->isRightType(bson::DOCUMENT);

        return Document(_value);
    }

    void Document::Element::getValue(Document &document) const {
        document = this->getValueDocument();
    }

    bool Document::Element::getValueBool() const {
        this->isRightType(bson::BOOL);

        return _value.at(0);
    }

    void Document::Element::getValue(bool &boolean) const {
        boolean = this->getValueBool();
    }

    std::nullptr_t Document::Element::getValueNullValue() const {
        this->isRightType(bson::NULLVALUE);

        return nullptr;
    }

    void Document::Element::getValue(std::nullptr_t &ptr) const {
        ptr = nullptr;
    }

    int32_t Document::Element::getValueInt32() const {
        this->isRightType(bson::INT32);

        union {
            int32_t integer;
            unsigned char bytes[4];
        } cutInteger;

        for (size_t i = 0; i < 4; ++i)
            cutInteger.bytes[i] = _value[i];

        return (IS_BIG_ENDIAN ? swap_endian<int32_t >(cutInteger.integer) : cutInteger.integer);
    }

    void Document::Element::getValue(int32_t &integer) const {
        integer = this->getValueInt32();
    }

    bool Document::Element::operator==(const Element &element) const {
        return this == &element || (_valueType == element._valueType &&
                                   _key == element._key &&
                                   _value == element._value);
    }

    bool Document::Element::operator!=(const Element &element) const {
        return !this->operator==(element);
    }

    Document::Document()
    : _nextInputType(Document::KEY) {
    }

    Document::Document(const Document &document) {
        this->operator=(document);
    }

    Document& Document::operator=(const Document &document) {
        if (this != &document) {
            _nextInputType = document._nextInputType;
            _lastKey = document._lastKey;
            _buffer = document._buffer;
            _elements = document._elements;
        }
        return *this;
    }

    Document::Document(const std::vector<unsigned char> &buffer)
    : _nextInputType(Document::KEY) {
        if (buffer.size() < 4)
            throw BsonException("The given document is invalid");

        union {
            int32_t integer;
            unsigned char bytes[4];
        } size;

        for (size_t i = 0; i < 4; ++i)
            size.bytes[i] = buffer.at(i);
        if (IS_BIG_ENDIAN)
            size.integer = swap_endian<int32_t >(size.integer);

        if (size.integer != buffer.size())
            throw BsonException("The given document is invalid");

        size_t bufferIndex = 4;
        while (bufferIndex < (buffer.size() - 1)) {
            _buffer.push_back(buffer.at(bufferIndex));
            bson::type valueType = codesTypes.at(buffer.at(bufferIndex));
            ++bufferIndex;

            std::string elementKey;
            while (buffer.at(bufferIndex)) {
                _buffer.push_back(buffer.at(bufferIndex));
                elementKey += buffer.at(bufferIndex);
                ++bufferIndex;
            }
            _lastKey = elementKey;

            _buffer.push_back(buffer.at(bufferIndex));
            ++bufferIndex;

            std::vector<unsigned char> elementBuffer;
            if (valueType == bson::STRING || valueType == bson::DOCUMENT) {
                size_t j = 0;
                for (size_t limitIndex = bufferIndex + 4; bufferIndex < limitIndex; ++bufferIndex) {
                    _buffer.push_back(buffer.at(bufferIndex));
                    elementBuffer.push_back(buffer.at(bufferIndex));
                    size.bytes[j] = buffer.at(bufferIndex);
                    ++j;
                }
                if (IS_BIG_ENDIAN)
                    size.integer = swap_endian<int32_t >(size.integer);
                for (size_t limitIndex = bufferIndex + size.integer; bufferIndex < limitIndex; ++bufferIndex) {
                    _buffer.push_back(buffer.at(bufferIndex));
                    elementBuffer.push_back(buffer.at(bufferIndex));
                }
            }
            else {
                for (size_t j = bufferIndex + typesSizes.at(valueType); bufferIndex < j; ++bufferIndex) {
                    _buffer.push_back(buffer.at(bufferIndex));
                    elementBuffer.push_back(buffer.at(bufferIndex));
                }
                ++bufferIndex;
            }
            this->insertElement(valueType, elementBuffer);
        }
    }

    Document::~Document() {
    }

    void Document::isInputValue() const {
        if (_nextInputType != Document::VALUE)
            throw BsonException("Next input into the document should be a key as a string.");
    }

    void Document::writeTypeCodeAndKey(unsigned char typeCode) {
        _buffer.push_back(typeCode);
        for (int i = 0; _lastKey[i]; ++i)
            _buffer.push_back((unsigned char &&) static_cast<unsigned char>(_lastKey[i]));
        _buffer.push_back('\x00');
    }

    void Document::insertElement(bson::type valueType, const std::vector<unsigned char> &elementBuffer) {
        Document::Element element(valueType, _lastKey, elementBuffer);
        _elements.insert(std::pair<const std::string, Element>(_lastKey, element));
    }

    std::vector<unsigned char> Document::getBuffer() const {
        std::vector<unsigned char> entireBuffer;

        union {
            int32_t integer;
            unsigned char bytes[4];
        } cutInteger;
        int32_t size = static_cast<int32_t >(_buffer.size() + 5);
        cutInteger.integer = (IS_BIG_ENDIAN ? swap_endian<int32_t>(size) : size);

        for (const auto &byte : cutInteger.bytes)
            entireBuffer.push_back(byte);
        for (const auto &byte : _buffer)
            entireBuffer.push_back(byte);
        entireBuffer.push_back('\x00');

        return entireBuffer;
    }

    Document &Document::operator<<(const char *string) {
        if (_nextInputType != Document::KEY)
            throw BsonException("A C string can only be used as a key.");

        std::string key(string);
        if (!key.size())
            throw BsonException("A key can't be empty.");

        _lastKey = key;
        _nextInputType = Document::VALUE;
        return *this;
    }

    Document &Document::operator<<(double floating) {
        this->isInputValue();

        union {
            double floating;
            unsigned char bytes[8];
        } cutFloating;
        cutFloating.floating = (IS_BIG_ENDIAN ? swap_endian<double>(floating) : floating);
        bson::type valueType = bson::DOUBLE;

        this->writeTypeCodeAndKey(typesCodes.at(valueType));
        std::vector<unsigned char> elementBuffer;
        for (const auto &byte : cutFloating.bytes) {
            _buffer.push_back(byte);
            elementBuffer.push_back(byte);
        }

        this->insertElement(valueType, elementBuffer);

        _nextInputType = KEY;

        return *this;
    }

    Document &Document::operator<<(const std::string &string) {
        if (_nextInputType == Document::KEY)
            *this << string.c_str();
        else {
            union {
                int32_t integer;
                unsigned char bytes[4];
            } cutInteger;
            int32_t size = static_cast<int32_t >(string.length() + 1);
            cutInteger.integer = (IS_BIG_ENDIAN ? swap_endian<int32_t>(size) : size);
            bson::type valueType = bson::STRING;

            this->writeTypeCodeAndKey(typesCodes.at(valueType));
            std::vector<unsigned char> elementBuffer;
            for (const auto &byte : cutInteger.bytes) {
                _buffer.push_back(byte);
                elementBuffer.push_back(byte);
            }
            for (const auto &character : string) {
                _buffer.push_back(static_cast<unsigned char>(character));
                elementBuffer.push_back(static_cast<unsigned char>(character));
            }
            _buffer.push_back('\x00');
            elementBuffer.push_back('\x00');

            this->insertElement(valueType, elementBuffer);

            _nextInputType = Document::KEY;
        }

        return *this;
    }

    Document &Document::operator<<(const Document &document) {
        this->isInputValue();

        const std::vector<unsigned char> &buffer = document.getBuffer();

        bson::type valueType = bson::DOCUMENT;

        this->writeTypeCodeAndKey(typesCodes.at(valueType));
        std::vector<unsigned char> elementBuffer;
        for (const auto &byte : buffer) {
            _buffer.push_back(byte);
            elementBuffer.push_back(byte);
        }

        this->insertElement(valueType, elementBuffer);

        _nextInputType = Document::KEY;
        return *this;
    }

    Document &Document::operator<<(bool boolean) {
        this->isInputValue();

        bson::type valueType = bson::BOOL;

        this->writeTypeCodeAndKey(typesCodes.at(valueType));
        std::vector<unsigned char> elementBuffer;
        _buffer.push_back(static_cast<unsigned char>(boolean));
        elementBuffer.push_back(static_cast<unsigned char>(boolean));

        this->insertElement(valueType, elementBuffer);

        _nextInputType = Document::KEY;
        return *this;
    }

    Document &Document::operator<<(std::nullptr_t) {
        this->isInputValue();

        bson::type valueType = bson::NULLVALUE;

        this->writeTypeCodeAndKey(typesCodes.at(valueType));

        this->insertElement(valueType, std::vector<unsigned char>());

        _nextInputType = Document::KEY;
        return *this;
    }

    Document &Document::operator<<(int32_t integer) {
        this->isInputValue();

        union {
            int32_t integer;
            unsigned char bytes[4];
        } cutInteger;
        cutInteger.integer = (IS_BIG_ENDIAN ? swap_endian<int32_t>(integer) : integer);
        bson::type valueType = bson::INT32;

        this->writeTypeCodeAndKey(typesCodes.at(valueType));
        std::vector<unsigned char> elementBuffer;
        for (const auto &byte : cutInteger.bytes) {
            _buffer.push_back(byte);
            elementBuffer.push_back(byte);
        }

        this->insertElement(valueType, elementBuffer);

        _nextInputType = Document::KEY;
        return *this;
    }

    Document &Document::operator<<(int64_t integer) {
        this->isInputValue();

        union {
            int64_t integer;
            unsigned char bytes[8];
        } cutInteger;
        cutInteger.integer = (IS_BIG_ENDIAN ? swap_endian<int64_t>(integer) : integer);
        bson::type valueType = bson::INT64;

        this->writeTypeCodeAndKey(typesCodes.at(valueType));
        std::vector<unsigned char> elementBuffer;
        for (const auto &byte : cutInteger.bytes) {
            _buffer.push_back(byte);
            elementBuffer.push_back(byte);
        }

        this->insertElement(valueType, elementBuffer);

        _nextInputType = Document::KEY;
        return *this;
    }

    const Document::Element& Document::operator[](const std::string &key) const {
        return _elements.at(key);
    }

    bool Document::operator==(const Document &document) const {
        return this == &document || (_nextInputType == document._nextInputType &&
                                    _lastKey == document._lastKey &&
                                    this->getBuffer() == document.getBuffer() &&
                                    _elements == document._elements);
    }

    bool Document::operator!=(const Document &document) const {
        return !this->operator==(document);
    }
}