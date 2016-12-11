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

    ASSERT_THROW(document << 42.42, bson::BsonException);
    ASSERT_THROW(document << document, bson::BsonException);
    ASSERT_THROW(document << true, bson::BsonException);
    ASSERT_THROW(document << nullptr, bson::BsonException);
    ASSERT_THROW(document << static_cast<int32_t >(42), bson::BsonException);
    ASSERT_THROW(document << static_cast<int64_t >(42), bson::BsonException);
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

/**
 * Check if the ask type match the stored one
 */
TEST(Miscellaneous, Ask_type_must_match) {
    bson::Document document;

    document << "keyDouble" << 42.42;
    document << "keyString" << std::string("test");
    document << "keyDocument" << bson::Document();
    document << "keyBool" << true;
    document << "keyNullValue" << nullptr;
    document << "keyInt32" << static_cast<int32_t >(42);
    document << "keyInt64" << static_cast<int64_t >(42);

    int32_t integer;
    double floating;

    EXPECT_THROW(document["keyDouble"].getValue(integer), bson::BsonException);
    EXPECT_THROW(document["keyString"].getValue(integer), bson::BsonException);
    EXPECT_THROW(document["keyDocument"].getValue(integer), bson::BsonException);
    EXPECT_THROW(document["keyBool"].getValue(integer), bson::BsonException);
    EXPECT_THROW(document["keyNullValue"].getValue(integer), bson::BsonException);
    EXPECT_THROW(document["keyInt32"].getValue(floating), bson::BsonException);
    EXPECT_THROW(document["keyInt64"].getValue(integer), bson::BsonException);
}

/**
 * Check if the document is complete before serialization
 */
TEST(Miscellaneous, Incomplete_Document) {
    bson::Document document;

    document << "test";
    ASSERT_THROW(document.getBuffer(), bson::BsonException);
}

TEST(Miscellaneous, Integration1) {
    bson::Document message;
    bson::Document tomato;
    bson::Document apple;

    tomato << "price" << 21;
    tomato << "vendor" << std::string(u8"Auchan");

    apple << "price" << 42;
    apple << "vendor" << std::string(u8"Carrefour");

    message << "tomato" << tomato
            << "apple" << apple;

    int tomatoPrice;
    tomatoPrice = tomato["price"].getValueInt32();
    std::string tomatoVendor;
    tomato["vendor"].getValue(tomatoVendor);

    int applePrice;
    applePrice = message["apple"].getValueDocument()["price"].getValueInt32();
    std::string appleVendor;
    message["apple"].getValueDocument()["vendor"].getValue(tomatoVendor);

    const std::vector<unsigned char> &buffer = message.getBuffer();
    bson::Document copyMessage(buffer);
}