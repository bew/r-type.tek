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
TEST(DESERIALIZATION, Double) {
    bson::Document document;

    document << u8"doubleKey" << 42.42;

    bson::Document::Element element =  document["doubleKey"];
    double floating;

    EXPECT_EQ(element.getValueType(), bson::DOUBLE);
    EXPECT_EQ(element.getKey(), u8"doubleKey");
    EXPECT_EQ(element.getValueDouble(), 42.42);
    element.getValue(floating);
    EXPECT_EQ(floating, 42.42);
}