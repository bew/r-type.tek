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
    };
}


#endif //BSON_DOCUMENT_HH
