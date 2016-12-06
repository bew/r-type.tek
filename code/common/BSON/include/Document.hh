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
#include "bson.hh"

/**
 * Namespace that contain all the BSON stuff
 */
namespace bson {
    /**
     * Represent a BSON document
     */
    class Document {
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
         * Store the BSON representation of the Document composed of all the given inputs
         */
        std::vector<unsigned char> _buffer;

    public:
        /**
         * Create an empty Document in order to serialize data into BSON and store them
         */
        Document();

        /**
         * Create a Document by copy and retrieve the values store from the given Document
         *
         * @param document the Document that need to be copy
         */

        Document(const Document &document);
        /**
         * Create a Document by assignment and retrieve the values store from the right Document
         *
         * @param document the Document that need to be copy
         * @return a Document containing the values of the Document pass in parameter
         */
        Document &operator=(const Document &document);

        /**
         * Destroy the Document
         */
        ~Document();

    private:
        /**
         * Check if the Document is waiting a value as an input
         *
         * @throw BsonException if the waiting input is not a value
         */
        void isInputValue() const;

        /**
         * Write the given typeCode followed by the last key received into the Document
         *
         * @param typeCode the typeCode to write into the Document
         */
        void writeTypeCodeAndKey(unsigned char typeCode);

    public:
        /**
         * Get the BSON representation of the Document
         *
         * @return the binarry buffer which is the BSON representation of the Document
         */
        std::vector<unsigned char> getBuffer() const;

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
        Document &operator<<(std::nullptr_t __attribute__((unused)) ptr);
        
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
    };
}


#endif //BSON_DOCUMENT_HH
