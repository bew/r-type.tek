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

/**
 * Check if the String deserialize correctly
 */
TEST(Deserialization, String) {
    bson::Document document;
    std::string key = u8"stringKey";
    std::string expected = u8"test";

    document << key << expected;

    bson::Document::Element element =  document[key];
    std::string string;

    EXPECT_EQ(element.getValueType(), bson::STRING);
    EXPECT_EQ(element.getKey(), key);
    EXPECT_EQ(element.getValueString (), expected);
    element.getValue(string);
    EXPECT_EQ(string, expected);
}

/**
 * Check if the Document deserialize correctly
 */
TEST(Deserialization, Document) {
    bson::Document expectedDocumentDouble;
    std::string keyDouble = u8"doubleKey";
    double expectedDouble = 42.42;
    expectedDocumentDouble << keyDouble << expectedDouble;

    bson::Document expectedDocumentString;
    std::string keyString = u8"stringKey";
    std::string expectedString = u8"test";
    expectedDocumentString << keyString << expectedString;

    bson::Document document;
    std::string keyDocumentDouble = u8"documentDouble";
    std::string keyDocumentString = u8"documentString";
    document << keyDocumentDouble << expectedDocumentDouble
             << keyDocumentString << expectedDocumentString;


    // Document Double
    bson::Document::Element elementDocumentDouble =  document[keyDocumentDouble];
    EXPECT_EQ(elementDocumentDouble.getValueType(), bson::DOCUMENT);
    EXPECT_EQ(elementDocumentDouble.getKey(), keyDocumentDouble);
    EXPECT_EQ(elementDocumentDouble.getValueDocument(), expectedDocumentDouble);
    bson::Document documentDouble;
    elementDocumentDouble.getValue(documentDouble);
    EXPECT_EQ(documentDouble, expectedDocumentDouble);

    // Double value
    bson::Document::Element elementDouble =  documentDouble[keyDouble];
    EXPECT_EQ(elementDouble.getValueType(), bson::DOUBLE);
    EXPECT_EQ(elementDouble.getKey(), keyDouble);
    EXPECT_EQ(elementDouble.getValueDouble(), expectedDouble);
    double floating;
    elementDouble.getValue(floating);
    EXPECT_EQ(floating, expectedDouble);

    // Document String
    bson::Document::Element elementDocumentString =  document[keyDocumentString];
    EXPECT_EQ(elementDocumentString.getValueType(), bson::DOCUMENT);
    EXPECT_EQ(elementDocumentString.getKey(), keyDocumentString);
    EXPECT_EQ(elementDocumentString.getValueDocument(), expectedDocumentString);
    bson::Document documentString;
    elementDocumentString.getValue(documentString);
    EXPECT_EQ(documentString, expectedDocumentString);

    // String value
    bson::Document::Element elementString =  documentString[keyString];
    EXPECT_EQ(elementString.getValueType(), bson::STRING);
    EXPECT_EQ(elementString.getKey(), keyString);
    EXPECT_EQ(elementString.getValueString(), expectedString);
    std::string string;
    elementString.getValue(string);
    EXPECT_EQ(string, expectedString);
}