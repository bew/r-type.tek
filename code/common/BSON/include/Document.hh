/**
 * @file Document.hh
 * @brief Class for BSON document
 * @author Christopher Paccard
 *
 * Represent a BSON document
 *
 */

#ifndef BSON_DOCUMENT_HH
#define BSON_DOCUMENT_HH

#include <vector>
#include <typeinfo>
#include "bson.hh"

/**
 * Namespace that contain all the BSON stuff
 */
namespace bson {
    /**
     * Represent a BSON document
     */
    class Document {
    public:
        /**
         * Class that will be used to hold an element (deserialization purpose)
         */
        class Element {
        private:
            /**
             * The type of the value stored inside the element
             */
            bson::type _valueType;

            /**
             * The key of the value stored inside the element
             */
            std::string _key;

            /**
             * The value inside the element as it's BSON representation
             */
            std::vector<unsigned char> _value;

        public:
            /**
             * Create an element from some information
             *
             * @param valueType the type of the value passed
             * @param key the key of the value passed
             * @param value the value as it's BSON representation
             */
            Element(bson::type valueType, const std::string &key, const std::vector<unsigned char> &value);

            /**
             * Create an Element by copy and retrieve the values stored from the given Element
             *
             * @param element the Element that need to be copy
             */
            Element(const Element &element);

            /**
             * Create a Element by assignment and retrieve the values stored from the right Element
             *
             * @param element the Element that need to be copy
             * @return a Element containing the values of the Element pass in parameter
             */
            Element& operator=(const Element &element);

            /**
             * Destroy the Element
             */
            ~Element(void);

        private:
            /**
             * Check if the Element's value type is of the type given in parameter
             *
             * @param valueType the type that need to match the Element's value type
             * @throw BsonException if the type given in parameter doesn't match the Element's value type
             */
            void isRightType(bson::type valueType) const;

        public:
            /**
             * Get the type of the value stored inside the Element
             *
             * @return the type of the value stored inside the Element
             */
            bson::type getValueType(void) const;

            /**
             * Get the value buffer
             *
             * @return the value buffer
             */
            const std::vector<unsigned char>& getValueBuffer(void) const;

            /**
             * Get the key of the value stored inside the Element
             *
             * @return the key of the value stored inside the Element
             */
            const std::string &getKey(void) const;

            /**
             * Get the double representation from the value stored in it's BSON representation
             *
             * @throw BsonException if the asked type is not the one stored
             * @return the double representation from the value stored in it's BSON representation
             */
            double getValueDouble(void) const;

            /**
             * Get the double representation from the value stored in it's BSON representation
             *
             * @throw BsonException if the asked type is not the one stored
             * @param[out] floating the double representation from the value stored in it's BSON representation
             */
            void getValue(double &floating) const;

            /**
             * Get the double representation from the value stored in it's BSON representation
             *
             * @throw BsonException if the asked type is not the one stored
             * @param[out] floating the double representation from the value stored in it's BSON representation
             */
            void operator>>(double &floating) const;

            /**
             * Get the string representation from the value stored in it's BSON representation
             *
             * @throw BsonException if the asked type is not the one stored
             * @return the string representation from the value stored in it's BSON representation
             */
            std::string getValueString(void) const;

            /**
             * Get the string representation from the value stored in it's BSON representation
             *
             * @throw BsonException if the asked type is not the one stored
             * @param[out] string the string representation from the value stored in it's BSON representation
             */
            void getValue(std::string &string) const;

            /**
             * Get the string representation from the value stored in it's BSON representation
             *
             * @throw BsonException if the asked type is not the one stored
             * @param[out] string the string representation from the value stored in it's BSON representation
             */
            void operator>>(std::string &string) const;

            /**
             * Get the Document representation from the value stored in it's BSON representation
             *
             * @throw BsonException if the asked type is not the one stored
             * @return the Document representation from the value stored in it's BSON representation
             */
            Document getValueDocument(void) const;

            /**
             * Get the Document representation from the value stored in it's BSON representation
             *
             * @throw BsonException if the asked type is not the one stored
             * @param[out] document the Document representation from the value stored in it's BSON representation
             */
            void getValue(Document &document) const;

            /**
             * Get the Document representation from the value stored in it's BSON representation
             *
             * @throw BsonException if the asked type is not the one stored
             * @param[out] document the Document representation from the value stored in it's BSON representation
             */
            void operator>>(Document &document) const;

            /**
             * Get the bool representation from the value stored in it's BSON representation
             *
             * @throw BsonException if the asked type is not the one stored
             * @return the bool representation from the value stored in it's BSON representation
             */
            bool getValueBool(void) const;

            /**
             * Get the bool representation from the value stored in it's BSON representation
             *
             * @throw BsonException if the asked type is not the one stored
             * @param[out] boolean the bool representation from the value stored in it's BSON representation
             */
            void getValue(bool &boolean) const;

            /**
             * Get the bool representation from the value stored in it's BSON representation
             *
             * @throw BsonException if the asked type is not the one stored
             * @param[out] boolean the bool representation from the value stored in it's BSON representation
             */
            void operator>>(bool &boolean) const;

            /**
             * Get the null value representation from the value stored in it's BSON representation
             *
             * @throw BsonException if the asked type is not the one stored
             * @return the null value representation from the value stored in it's BSON representation
             */
            std::nullptr_t getValueNullValue(void) const;

            /**
             * Get the null value representation from the value stored in it's BSON representation
             *
             * @throw BsonException if the asked type is not the one stored
             * @param[out] ptr the null value representation from the value stored in it's BSON representation
             */
            void getValue(std::nullptr_t &ptr) const;

            /**
             * Get the null value representation from the value stored in it's BSON representation
             *
             * @throw BsonException if the asked type is not the one stored
             * @param[out] ptr the null value representation from the value stored in it's BSON representation
             */
            void operator>>(std::nullptr_t &ptr) const;

            /**
             * Get the int32 representation from the value stored in it's BSON representation
             *
             * @throw BsonException if the asked type is not the one stored
             * @return the int32 representation from the value stored in it's BSON representation
             */
            int32_t getValueInt32(void) const;

            /**
             * Get the int32 representation from the value stored in it's BSON representation
             *
             * @throw BsonException if the asked type is not the one stored
             * @param[out] integer the int32 representation from the value stored in it's BSON representation
             */
            void getValue(int32_t &integer) const;

            /**
             * Get the int32 representation from the value stored in it's BSON representation
             *
             * @throw BsonException if the asked type is not the one stored
             * @param[out] integer the int32 representation from the value stored in it's BSON representation
             */
            void operator>>(int32_t &integer) const;

            /**
             * Get the int64 representation from the value stored in it's BSON representation
             *
             * @throw BsonException if the asked type is not the one stored
             * @return the int64 representation from the value stored in it's BSON representation
             */
            int64_t getValueInt64(void) const;

            /**
             * Get the int64 representation from the value stored in it's BSON representation
             *
             * @throw BsonException if the asked type is not the one stored
             * @param[out] integer the int64 representation from the value stored in it's BSON representation
             */
            void getValue(int64_t &integer) const;

            /**
             * Get the int64 representation from the value stored in it's BSON representation
             *
             * @throw BsonException if the asked type is not the one stored
             * @param[out] integer the int64 representation from the value stored in it's BSON representation
             */
            void operator>>(int64_t &integer) const;

            /**
             * Compare if two Elements are the same
             *
             * @param element the second Element to compare
             * @return true if the Elements are the same else false
             */
            bool operator==(const Element& element) const;

            /**
             * Compare if two Elements aren't the same
             *
             * @param element the second Element to compare
             * @return true if the Elements aren't the same else false
             */
            bool operator!=(const Element& element) const;
        };

    private:
        /**
         * The input types the Document can have
         */
        enum inputTypes {
            KEY,
            VALUE
        };

        /**
         * Store the next input type the document need to receive
         */
        inputTypes _nextInputType;

        /**
         * Store the last key given
         */
        std::string _lastKey;

        /**
         * Store the BSON representation of the Document composed of all the given inputs as Element usable
         */
        std::map<const std::string, Document::Element> _elements;

    public:
        /**
         * Create an empty Document in order to serialize data into BSON and store them
         */
        Document(void);

        /**
         * Create a Document by copy and retrieve the values stored from the given Document
         *
         * @param document the Document that need to be copy
         */
        Document(const Document &document);

        /**
         * Create a Document by assignment and retrieve the values stored from the right Document
         *
         * @param document the Document that need to be copy
         * @return a Document containing the values of the Document pass in parameter
         */
        Document &operator=(const Document &document);

        /**
         * Create a Document by deserialization of the given buffer which is a valid BSON representation of a Document
         *
         * @param buffer the buffer which will be deserialiazed to get the Document
         * @throw BsonException if the given buffer is invalid
         */
        Document(const std::vector<unsigned char> &buffer);

        /**
         * Destroy the Document
         */
        ~Document(void);

    private:
        /**
         * Check if the Document is waiting a value as an input
         *
         * @throw BsonException if the waiting input is not a value
         */
        void isInputValue(void) const;

        /**
         * Insert an element inside the document with the given information
         * The key will be find in _lastKey attribute
         *
         * @param valueType the type of the value stored inside the element
         * @param elementBuffer the value to stored inside the element as it's BSON representation
         */
        void insertElement(bson::type valueType, const std::vector<unsigned char> &elementBuffer);

    public:
        /**
         * Get the BSON representation of the Document
         *
         * @throw BsonException if the document is incomplete (next input is not key)
         * @return the binary buffer which is the BSON representation of the Document
         */
        std::vector<unsigned char> getBuffer(void) const;

        /**
         * Add a string as key into the Document
         *
         * @param string the string to add
         * @throw BsonException if the waiting input is not a key
         * @throw BsonException if the key is empty
         * @return the Document with the string added
         */
        Document &operator<<(const char *string);

        /**
         * Add a double into the Document
         *
         * @param floating the double to add
         * @throw BsonException if the waiting input is not a value
         * @return the Document with the double added
         */
        Document &operator<<(double floating);

        /**
         * Add a string as a key or as a value into the Document
         *
         * @param string the string to add
         * @throw BsonException if the input should be a key and something went wrong
         * @return the Document with the string added
         */
        Document &operator<<(const std::string &string);
        
        /**
         * Add a Document into the Document
         * 
         * @param document the Document to add
         * @throw BsonException if the waiting input is not a value
         * @return the Document with the Document added
         */
        Document &operator<<(const Document &document);
        
        /**
         * Add a bool into the Document
         * 
         * @param boolean the bool to add
         * @throw BsonException if the waiting input is not a value
         * @return the Document with the bool added
         */
        Document &operator<<(bool boolean);
        
        /**
         * Add a null value into the Document
         * 
         * @param ptr the pointer as a null value
         * @throw BsonException if the waiting input is not a value
         * @return the Document with the null value added
         */
        Document &operator<<(std::nullptr_t ptr);
        
        /**
         * Add a int32 into the Document
         * 
         * @param integer the int32 to add
         * @throw BsonException if the waiting input is not a value
         * @return the Document with the int32 added
         */
        Document &operator<<(int32_t integer);

        /**
         * Add a int64 into the Document
         * 
         * @param integer the int64 to add
         * @throw BsonException if the waiting input is not a value
         * @return the Document with the int64 added
         */
        Document &operator<<(int64_t integer);

        /**
         * Get the Element linked to the given key which is the representation of a value inside the BSON representation of the Document
         *
         * @param key the key of the Element to get
         * @throw std::out_of_range if the key doesn't exist
         * @return the Element of the given key with the value stored in it
         */
        const Document::Element& operator[](const std::string &key) const;

        /**
         * Compare if two Documents are the same
         *
         * @param document the second Document to compare
         * @return true if the Documents are the same else false
         */
        bool operator==(const Document &document) const;

        /**
         * Compare if two Documents aren't the same
         *
         * @param document the second Document to compare
         * @return true if the Documents aren't the same else false
         */
        bool operator!=(const Document &document) const;

        /**
         * Check if the Document contain the specified key
         * 
         * @param key the key to check 
         * @return true if the Document contain the key else false
         */
        bool hasKey(const std::string& key) const;
        
        /**
         * Get the list of keys inside the Document
         * 
         * @return a vector of strings which represent the keys 
         */
        std::vector<std::string> getKeys(void) const;
        
        /**
         * Get the number of Elements inside the Document
         * 
         * @return the number of Elements inside the Document
         */
        size_t elementsCount(void) const;
        
        /**
         * Check if the Document is empty
         * 
         * @return true if the Document is empty else false
         */
        bool isEmpty(void) const;

        /**
         * Get the Elements inside the Document
         *
         * @return the Elements inside the Document
         */
        const std::map<const std::string, Document::Element>& getElements(void) const;

        /**
         * Clear the Document (empty it)
         */
        void clear(void);
    };
}


#endif //BSON_DOCUMENT_HH
