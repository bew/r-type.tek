/**
 * @file bson.hh
 * @brief Namespace for BSON stuff
 * @author Christopher Paccard
 *
 * Namespace that contain all the BSON stuff
 *
 */

#ifndef BSON_HH
#define BSON_HH

#include <map>
#include <stdexcept>
#include <string>

/**
 * Namespace that contain all the BSON stuff
 */
namespace bson {
    /**
     * Detail all the types handled
     */
    enum type {
        DOUBLE,
        STRING,
        DOCUMENT,
        BOOL,
        NULLVALUE,
        INT32,
        INT64
    };

    /**
     * A map where the types are the keys and the codes the values
     */
    static const std::map<bson::type, unsigned char> typesCodes = {
            {bson::DOUBLE, '\x01'},
            {bson::STRING, '\x02'},
            {bson::DOCUMENT, '\x03'},
            {bson::BOOL, '\x08'},
            {bson::NULLVALUE, '\x0A'},
            {bson::INT32, '\x10'},
            {bson::INT64, '\x12'},
    };

    /**
     * A map where the codes are the keys and the types the values
     */
    static const std::map<unsigned char, bson::type> codesTypes = {
            {'\x01', bson::DOUBLE},
            {'\x02', bson::STRING},
            {'\x03', bson::DOCUMENT},
            {'\x08', bson::BOOL},
            {'\x0A', bson::NULLVALUE},
            {'\x10', bson::INT32},
            {'\x12', bson::INT64},
    };

    /**
     * A map where the types are the keys and the type's size are the values
     */
    static const std::map<bson::type, size_t> typesSizes = {
            {bson::DOUBLE, 8},
            {bson::BOOL, 1},
            {bson::NULLVALUE, 0},
            {bson::INT32, 4},
            {bson::INT64, 8},
    };

    /**
     * A map where the types are the keys and their name are the values
     */
    static const std::map<bson::type, std::string> enumString = {
            {bson::DOUBLE, "double"},
            {bson::STRING, "string"},
            {bson::DOCUMENT, "document"},
            {bson::BOOL, "bool"},
            {bson::NULLVALUE, "null"},
            {bson::INT32, "int32"},
            {bson::INT64, "int64"},
    };

    /**
     * The generic exception for BSON
     */
    class BsonException : public std::runtime_error {
    public:
        /**
         * Create a BsonException with the given string for detail
         *
         * @param e the detail string
         */
        BsonException(const std::string &e) : std::runtime_error(e) {}
    };
}

#endif //BSON_HH
