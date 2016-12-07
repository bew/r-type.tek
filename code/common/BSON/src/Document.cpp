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
#include <iostream>


namespace bson {

    Document::Element::Element(type valueType, const std::string &key, const std::vector<unsigned char> &value)
    : _valueType(valueType), _key(key), _value(value)  {
    }

    Document::Element::Element(const Element &element) {
        if (this != &element) {
            _valueType = element._valueType;
            _key = element._key;
            _value = element._value;
        }
    }

    Document::Element& Document::Element::operator=(const Element &element) {
        if (this != &element) {
            _key = element._key;
            _value = element._value;
        }
        return *this;
    }

    Document::Element::~Element() {
    }

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
            throw BsonException("Next input into the document should be a key as a string.");
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
        if (_nextInputType != KEY)
            throw BsonException("A C string can only be used as a key.");

        std::string key(string);
        if (!key.size())
            throw BsonException("A key can't be empty.");

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
        cutFloating.floating = (IS_BIG_ENDIAN ? swap_endian<double>(floating) : floating);
        type valueType = DOUBLE;

        this->writeTypeCodeAndKey(typesCodes.at(valueType));
        std::vector<unsigned char> elementBuffer;
        for (const auto &byte : cutFloating.bytes) {
            _buffer.push_back(byte);
            elementBuffer.push_back(byte);
        }

        Element element(valueType, _lastKey, elementBuffer);
        _elements.insert(std::pair<const std::string, Element>(_lastKey, element));

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
            int32_t size = static_cast<int32_t >(string.length() + 1);
            cutInteger.integer = (IS_BIG_ENDIAN ? swap_endian<int32_t>(size) : size);
            type valueType = STRING;

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

            Element element(valueType, _lastKey, elementBuffer);
            _elements.insert(std::pair<const std::string, Element>(_lastKey, element));

            _nextInputType = KEY;
        }

        return *this;
    }

    Document &Document::operator<<(const Document &document) {
        this->isInputValue();

        const std::vector<unsigned char> &buffer = document.getBuffer();

        type valueType = DOCUMENT;

        this->writeTypeCodeAndKey(typesCodes.at(valueType));
        std::vector<unsigned char> elementBuffer;
        for (const auto &byte : buffer) {
            _buffer.push_back(byte);
            elementBuffer.push_back(byte);
        }

        Element element(valueType, _lastKey, elementBuffer);
        _elements.insert(std::pair<const std::string, Element>(_lastKey, element));

        _nextInputType = KEY;
        return *this;
    }

    Document &Document::operator<<(bool boolean) {
        this->isInputValue();

        type valueType = BOOL;

        this->writeTypeCodeAndKey(typesCodes.at(valueType));
        std::vector<unsigned char> elementBuffer;
        _buffer.push_back(static_cast<unsigned char>(boolean));
        elementBuffer.push_back(static_cast<unsigned char>(boolean));

        Element element(valueType, _lastKey, elementBuffer);
        _elements.insert(std::pair<const std::string, Element>(_lastKey, element));

        _nextInputType = KEY;
        return *this;
    }

    Document &Document::operator<<(std::nullptr_t) {
        this->isInputValue();

        type valueType = NULLVALUE;

        this->writeTypeCodeAndKey(typesCodes.at(valueType));

        Element element(valueType, _lastKey, std::vector<unsigned char>());
        _elements.insert(std::pair<const std::string, Element>(_lastKey, element));

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
        cutInteger.integer = (IS_BIG_ENDIAN ? swap_endian<int32_t>(integer) : integer);
        type valueType = INT32;

        this->writeTypeCodeAndKey(typesCodes.at(valueType));
        std::vector<unsigned char> elementBuffer;
        for (const auto &byte : cutInteger.bytes) {
            _buffer.push_back(byte);
            elementBuffer.push_back(byte);
        }

        Element element(valueType, _lastKey, std::vector<unsigned char>());
        _elements.insert(std::pair<const std::string, Element>(_lastKey, element));

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
        cutInteger.integer = (IS_BIG_ENDIAN ? swap_endian<int64_t>(integer) : integer);
        type valueType = INT64;

        this->writeTypeCodeAndKey(typesCodes.at(valueType));
        std::vector<unsigned char> elementBuffer;
        for (const auto &byte : cutInteger.bytes) {
            _buffer.push_back(byte);
            elementBuffer.push_back(byte);
        }

        Element element(valueType, _lastKey, std::vector<unsigned char>());
        _elements.insert(std::pair<const std::string, Element>(_lastKey, element));

        _nextInputType = KEY;
        return *this;
    }

    Document::Element& Document::operator[](const std::string &key) {
        return _elements.at(key);
    }
}