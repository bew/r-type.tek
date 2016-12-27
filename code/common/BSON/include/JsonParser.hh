/**
 * @file JsonParser.hh
 * @brief Class for JsonParser
 * @author Christopher Paccard
 *
 * Allow to parse JSON to BSON
 *
 */

#ifndef BSON_JSONPARSER_HH
#define BSON_JSONPARSER_HH

#include <string>
#include <map>
#include "Document.hh"

namespace bson {
    class Document;
}

#ifndef SAVE_CONTEXT
# define SAVE_CONTEXT std::string::iterator tmpPos = _pos
#endif  // !SAVE_CONTEXT

#ifndef RESTORE_CONTEXT
# define RESTORE_CONTEXT _pos = tmpPos
#endif  // !RESTORE_CONTEXT

/**
 * Namespace that contain all the BSON stuff
 */
namespace bson {
    class JsonParser {
    private:
        /**
         * Store the JSON to parse
         */
        std::string _json;

        /**
         * Position on the JSON string
         */
        std::string::iterator _pos;

        /**
         * Store all the tags for capture purpose
         */
        std::map<std::string, std::string::iterator> _tags;

    public:
        /**
         * Ctor
         */
        JsonParser(const std::string &json);

        JsonParser(const JsonParser &jsonParser) = delete;

        JsonParser &operator=(const JsonParser &jsonParser) = delete;

        /**
         * Dtor
         */
        ~JsonParser(void);

        /**
         * Parse the JSON given in the ctor an return it's BSON representation as a Document
         *
         * @throw BsonException if cna't parse JSON
         * @return the BSON representation of the JSON as a Document
         */
        bson::Document parse(void);

    private:
        /**
         * Format a string for better error message
         *
         * @param string the string to append to the message
         * @return a formatted string for better error message
         */
        std::string getErrorMessage(const std::string &string) const;

        /**
         * Allow to begin to capture a string frame and tag it in order to retrieve it later
         *
         * @param tag the tag for this frame of the string to capture
         * @return true if there is something to capture, else false
         */
        bool beginCapture(const std::string &tag);

        /**
         * Allow to end the capture of a string frame and retrieve it depending on the tag
         *
         * @param tag the frame we want to retrieve
         * @param[out] out the string representing the frame
         * @return true if there is something captured, else false
         */
        bool endCapture(const std::string &tag, std::string &out);

        /**
         * Check if the position is on this character
         *
         * @param c the character to check
         * @return true if it's the same character, else false
         */
        bool peekChar(char c) const;

        /**
         * Read the character if the position is on this character
         *
         * @param c the character to read
         * @return true if it's the same character, else false
         */
        bool readChar(char c);

        /**
         * Read the digit if the position is on one of them
         *
         * @return true if it's a digit, else false
         */
        bool readDigit();

        /**
         * Read the string until the position it's on the character
         *
         * @param c the character to stop
         * @return true if the position it's on the character, else false
         */
        bool readUntil(char c);

        /**
         * Read the text and check if match the given string
         *
         * @param string the string that need to match the text
         * @return true if it's match, else false
         */
        bool readText(const std::string &string);

        /**
         * Allow to pass all the blanks (spaces and tabs)
         */
        void ignoreBlanks(void);

        /**
         * Read a double and store it inside the given Document
         * 
         * @param document the Document where to store the double
         * @return true if the double has been stored, else false
         */
        bool readDouble(bson::Document &document);

        /**
         * Read a string and store it inside the given Document
         * 
         * @param document the Document where to store the string
         * @throw BsonException if string is not terminated
         * @return true if the string has been stored, else false
         */
        bool readString(bson::Document &document);

        /**
         * Read a JSON object (BSON Document) and store it inside the given Document
         *
         * @param document the Document where to store the JSON object
         * @throw BsonException if object is malformated
         * @return true if the JSON object has been stored, else false
         */
        bool readObject(bson::Document &document);

        /**
         * Read a JSON array (BSON Document) and store it inside the given Document
         *
         * @param document the Document where to store the JSON array
         * @throw BsonException if array is malformated
         * @return true if the JSON object has been stored, else false
         */
        bool readArray(bson::Document &document);

        /**
         * Read a bool and store it inside the given Document
         * 
         * @param document the Document where to store the bool
         * @return true if the bool has been stored, else false
         */
        bool readBool(bson::Document &document);

        /**
         * Read a null and store it inside the given Document
         * 
         * @param document the Document where to store the null
         * @return true if the null has been stored, else false
         */
        bool readNull(bson::Document &document);

        /**
         * Read a integer and store it inside the given Document
         * 
         * @param document the Document where to store the integer
         * @return true if the integer has been stored, else false
         */
        bool readInteger(bson::Document &document);
    };
}

#endif //BSON_JSONPARSER_HH
