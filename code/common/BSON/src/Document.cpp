/**
 * @file Document.cpp
 * @brief Class for BSON document
 * @author Christopher Paccard
 *
 * Represent a BSON document
 *
 */

#include <iostream>
#include <fstream>
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

    const std::vector<unsigned char>& Document::Element::getValueBuffer() const {
        return _value;
    }

    const std::string& Document::Element::getKey() const {
        return _key;
    }

    void Document::Element::toJson(unsigned int spaces) const {
        std::cout << std::string(spaces, ' ' ) << '"' << this->getKey() << "\": ";
        switch (_valueType) {
            case (bson::DOUBLE):
                std::cout << this->getValueDouble();
                break;
            case (bson::STRING):
                std::cout << '"' << this->getValueString() << '"';
                break;
            case (bson::DOCUMENT):
                this->getValueDocument().toJSON(spaces, false);
                break;
            case (bson::BOOL):
                std::cout << std::boolalpha << this->getValueBool() << std::noboolalpha;
                break;
            case (bson::NULLVALUE):
                std::cout << "null";
                break;
            case (bson::INT32):
                std::cout << this->getValueInt32();
                break;
            case (bson::INT64):
                std::cout << this->getValueInt64();
                break;
        }
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

    void Document::Element::operator>>(double &floating) const {
        floating = this->getValueDouble();
    }

    std::string Document::Element::getValueString() const {
        this->isRightType(bson::STRING);

        return std::string(_value.begin() + 4, _value.end() - 1);
    }

    void Document::Element::getValue(std::string &string) const {
        string = this->getValueString();
    }

    void Document::Element::operator>>(std::string &string) const {
        string = this->getValueString();
    }

    Document Document::Element::getValueDocument() const {
        this->isRightType(bson::DOCUMENT);

        return Document(_value);
    }

    void Document::Element::getValue(Document &document) const {
        document = this->getValueDocument();
    }

    void Document::Element::operator>>(Document &document) const {
        document = this->getValueDocument();
    }

    Document::Element Document::Element::operator[](const std::string &key) const {
        Document document = this->getValueDocument();
        return document[key];
    }

    bool Document::Element::getValueBool() const {
        this->isRightType(bson::BOOL);

        return _value.at(0) == 1;
    }

    void Document::Element::getValue(bool &boolean) const {
        boolean = this->getValueBool();
    }

    void Document::Element::operator>>(bool &boolean) const {
        boolean = this->getValueBool();
    }

    std::nullptr_t Document::Element::getValueNullValue() const {
        this->isRightType(bson::NULLVALUE);

        return nullptr;
    }

    void Document::Element::getValue(std::nullptr_t &ptr) const {
        ptr = nullptr;
    }

    void Document::Element::operator>>(std::nullptr_t &ptr) const {
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

    void Document::Element::operator>>(int32_t &integer) const {
        integer = this->getValueInt32();
    }

    int64_t Document::Element::getValueInt64() const {
        this->isRightType(bson::INT64);

        union {
            int64_t integer;
            unsigned char bytes[8];
        } cutInteger;

        for (size_t i = 0; i < 8; ++i)
            cutInteger.bytes[i] = _value[i];

        return (IS_BIG_ENDIAN ? swap_endian<int64_t >(cutInteger.integer) : cutInteger.integer);
    }

    void Document::Element::getValue(int64_t &integer) const {
        integer = this->getValueInt64();
    }

    void Document::Element::operator>>(int64_t &integer) const {
        integer = this->getValueInt64();
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
            _elements = document._elements;
        }
        return *this;
    }

    Document::Document(const std::vector<unsigned char> &buffer) : _nextInputType(Document::KEY) {
        this->unserializeBuffer(buffer);
    }

    Document::Document(const std::string &buffer) : _nextInputType(Document::KEY) {
        this->unserializeBuffer(std::vector<unsigned char>(buffer.begin(), buffer.end()));
    }

    Document::~Document() {
    }

    void Document::isInputValue() const {
        if (_nextInputType != Document::VALUE)
            throw BsonException("Next input into the document should be a key as a string.");
    }

    void Document::insertElement(bson::type valueType, const std::vector<unsigned char> &elementBuffer) {
        Document::Element newElement(valueType, _lastKey, elementBuffer);

        size_t i = 0;
        for (const auto &element : _elements) {
            if (element.getKey() == _lastKey) {
                _elements[i] = newElement;
                return ;
            }
            ++i;
        }

        _elements.push_back(newElement);
    }

    void Document::unserializeBuffer(const std::vector<unsigned char> &buffer) {
        if (_nextInputType != Document::KEY)
            throw BsonException("Can't unserialize while having incomplete an Document (next input should be a key)");

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
            bson::type valueType = codesTypes.at(buffer.at(bufferIndex));
            ++bufferIndex;

            std::string elementKey;
            while (buffer.at(bufferIndex)) {
                elementKey += buffer.at(bufferIndex);
                ++bufferIndex;
            }
            _lastKey = elementKey;

            ++bufferIndex;

            std::vector<unsigned char> elementBuffer;
            if (valueType == bson::STRING || valueType == bson::DOCUMENT) {
                size_t j = 0;
                for (size_t limitIndex = bufferIndex + 4; bufferIndex < limitIndex; ++bufferIndex) {
                    elementBuffer.push_back(buffer.at(bufferIndex));
                    size.bytes[j] = buffer.at(bufferIndex);
                    ++j;
                }
                if (IS_BIG_ENDIAN)
                    size.integer = swap_endian<int32_t >(size.integer);
                if (valueType == bson::DOCUMENT)
                    size.integer -= 4;
                for (size_t limitIndex = bufferIndex + (size.integer); bufferIndex < limitIndex; ++bufferIndex)
                    elementBuffer.push_back(buffer.at(bufferIndex));
            }
            else {
                for (size_t j = bufferIndex + typesSizes.at(valueType); bufferIndex < j; ++bufferIndex)
                    elementBuffer.push_back(buffer.at(bufferIndex));
            }
            this->insertElement(valueType, elementBuffer);
        }
    }

    std::vector<unsigned char> Document::getBuffer() const {
        if (_nextInputType != Document::KEY)
            throw BsonException("Incomplete document (next input should be a key)");

        std::vector<unsigned char> entireBuffer;
        std::vector<unsigned char> elementsBuffer;

        for (const auto& element : _elements) {
            elementsBuffer.push_back(typesCodes.at(element.getValueType()));
            std::string key = element.getKey();
            for (int i = 0; key[i]; ++i)
                elementsBuffer.push_back(static_cast<unsigned char>(key[i]));
            elementsBuffer.push_back('\x00');
            elementsBuffer.insert(elementsBuffer.end(), element.getValueBuffer().begin(), element.getValueBuffer().end());
        }

        union {
            int32_t integer;
            unsigned char bytes[4];
        } cutInteger;
        int32_t size = static_cast<int32_t >(elementsBuffer.size() + 5);
        cutInteger.integer = (IS_BIG_ENDIAN ? swap_endian<int32_t>(size) : size);

        for (const auto &byte : cutInteger.bytes)
            entireBuffer.push_back(byte);
        entireBuffer.insert(entireBuffer.end(), elementsBuffer.begin(), elementsBuffer.end());
        entireBuffer.push_back('\x00');

        return entireBuffer;
    }

    std::string Document::getBufferString() const {
        std::vector<unsigned char> buffer = this->getBuffer();
        return std::string(buffer.begin(), buffer.end());
    }

    void Document::writeToFile(const std::string &filename) const {
        std::ofstream file(filename, std::ofstream::out | std::ofstream::app);
        if (!file.is_open())
            throw BsonException(std::string("Can't open file: ") + filename);
        file << this->getBufferString();
        file.close();
    }

    std::ostream& Document::writeToStream(std::ostream &os) const {
        os << this->getBufferString();
        return os;
    }

    void Document::readFromFile(const std::string &filename) {
        std::ifstream file(filename, std::ios::in | std::ios::binary | std::ios::ate);

        if (!file.is_open())
            throw BsonException(std::string("Can't open file: ") + filename);

        std::ifstream::pos_type fileSize = file.tellg();
        file.seekg(0, std::ios::beg);

        std::vector<char> bytes(fileSize);
        file.read(&bytes[0], fileSize);

        this->unserializeBuffer(std::vector<unsigned char>(bytes.begin(), bytes.end()));
    }

    void Document::toJSON(unsigned int spaces, bool newLine) const {
        bool first = true;
        std::cout << "{" << std::endl;
        for (const auto& element : _elements) {
            if (!first)
                std::cout << ',' << std::endl;
            element.toJson(spaces + 2);
            first = false;
        }
        std::cout << std::endl << std::string(spaces, ' ' ) << "}";
        if (newLine)
            std::cout << std::endl;
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

        std::vector<unsigned char> elementBuffer;
        for (const auto &byte : cutFloating.bytes)
            elementBuffer.push_back(byte);

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

            std::vector<unsigned char> elementBuffer;
            for (const auto &byte : cutInteger.bytes)
                elementBuffer.push_back(byte);
            for (const auto &character : string)
                elementBuffer.push_back(static_cast<unsigned char>(character));
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

        std::vector<unsigned char> elementBuffer;
        for (const auto &byte : buffer)
            elementBuffer.push_back(byte);

        this->insertElement(valueType, elementBuffer);

        _nextInputType = Document::KEY;
        return *this;
    }

    Document &Document::operator<<(bool boolean) {
        this->isInputValue();

        bson::type valueType = bson::BOOL;

        std::vector<unsigned char> elementBuffer;
        elementBuffer.push_back(static_cast<unsigned char>(boolean));

        this->insertElement(valueType, elementBuffer);

        _nextInputType = Document::KEY;
        return *this;
    }

    Document &Document::operator<<(std::nullptr_t) {
        this->isInputValue();

        bson::type valueType = bson::NULLVALUE;

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

        std::vector<unsigned char> elementBuffer;
        for (const auto &byte : cutInteger.bytes)
            elementBuffer.push_back(byte);

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

        std::vector<unsigned char> elementBuffer;
        for (const auto &byte : cutInteger.bytes)
            elementBuffer.push_back(byte);

        this->insertElement(valueType, elementBuffer);

        _nextInputType = Document::KEY;
        return *this;
    }

    const Document::Element& Document::operator[](const std::string &key) const {
        for (const auto &element : _elements) {
            if (element.getKey() == key)
                return element;
        }
        throw BsonException("No such key inside the Document");
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

    bool Document::hasKey(const std::string &key) const {
        for (const auto &element : _elements) {
            if (element.getKey() == key)
                return true;
        }
        return false;
    }

    std::vector<std::string> Document::getKeys() const {
        std::vector<std::string> keys;
        
        for (const auto& element : _elements)
            keys.push_back(element.getKey());
        
        return keys;
    }
    
    size_t Document::elementsCount() const {
        return _elements.size();
    }
    
    bool Document::isEmpty() const {
        return _elements.size() == 0;
    }

    const std::vector<bson::Document::Element>& Document::getElements() const {
        return _elements;
    }

    void Document::clear() {
        _nextInputType = Document::KEY;
        _elements.clear();
    }

}