/**
 * @file serialization.cpp
 * @brief Serialization test file
 * @author Christopher Paccard
 *
 * Contain all the the test to check serialization
 *
 */

#include "Document.hh"
#include <gtest/gtest.h>

/**
 * Check if the double serialize correctly
 */
TEST(Serialization, Double) {
    bson::Document document;

    document << "doubleKey" << 42.42;

    const std::vector<unsigned char> &retrievedBuffer = document.getBuffer();
    const std::vector<unsigned char> expectedBuffer = {24, 0, 0, 0,                                   // size of document
                                                       1,                                             // id for double element
                                                       100, 111, 117, 98, 108, 101, 75, 101, 121, 0,  // e_name of the value
                                                       246, 40, 92, 143, 194, 53, 69, 64,             // value of the double
                                                       0};                                            // end of document

    ASSERT_EQ(retrievedBuffer, expectedBuffer);
}
