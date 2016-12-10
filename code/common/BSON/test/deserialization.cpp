/**
 * @file deserialization.cpp
 * @brief Deserialization test file
 * @author Christopher Paccard
 *
 * Contain all the the test to check deserialization
 *
 */

#include <gtest/gtest.h>
#include "Document.hh"

/**
 * Check if the double deserialize correctly
 */
TEST(Deserialization, Double) {
    bson::Document document;
    std::string key = u8"doubleKey";
    double expected = 42.42;

    document << key << expected;

    bson::Document::Element element =  document[key];
    double floating;

    EXPECT_EQ(element.getValueType(), bson::DOUBLE);
    EXPECT_EQ(element.getKey(), key);
    EXPECT_EQ(element.getValueDouble(), expected);
    element.getValue(floating);
    EXPECT_EQ(floating, expected);
}

TEST(Deserialization, String) {
    bson::Document document;
    std::string key = u8"stringKey";
    std::string expected = u8"toto42sh";

    document << key << expected;

    bson::Document::Element element =  document[key];
    std::string string;

    EXPECT_EQ(element.getValueType(), bson::STRING);
    EXPECT_EQ(element.getKey(), key);
    EXPECT_EQ(element.getValueString (), expected);
    element.getValue(string);
    EXPECT_EQ(string, expected);
}