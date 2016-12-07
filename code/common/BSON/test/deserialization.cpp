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

    document["doubleKey"];
}