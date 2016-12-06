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

TEST(Miscellaneous, Value_cant_be_key) {
    bson::Document document;

    EXPECT_THROW(document << 42, bson::BsonException);
}


TEST(Miscellaneous, C_string_can_only_be_key) {
    bson::Document document;

    document << u8"stringKey";

    EXPECT_THROW(document << u8"toto", bson::BsonException);
}

TEST(Miscellaneous, Key_cant_be_empty) {
    bson::Document document;

    EXPECT_THROW(document << u8"", bson::BsonException);
}