/**
 * @file miscellaneous.cpp
 * @brief Miscellaneous test file
 * @author Christopher Paccard
 *
 * Contain miscellaneous test
 *
 */

#include <gtest/gtest.h>
#include "Document.hh"

/**
 * Check if a value can't be a key
 */
TEST(Miscellaneous, Value_cant_be_key) {
    bson::Document document;

    ASSERT_THROW(document << 42, bson::BsonException);
}

/**
* Check if C string can only be a key
*/
TEST(Miscellaneous, C_string_can_only_be_key) {
    bson::Document document;

    document << u8"stringKey";

    ASSERT_THROW(document << u8"toto", bson::BsonException);
}

/**
 * Check if a key can't be empty
 */
TEST(Miscellaneous, Key_cant_be_empty) {
    bson::Document document;

    ASSERT_THROW(document << u8"", bson::BsonException);
}

/**
 * Check if a key must exist
 */
TEST(Miscellaneous, Key_must_exist) {
    bson::Document document;

    ASSERT_THROW(document["none"], std::out_of_range);
}