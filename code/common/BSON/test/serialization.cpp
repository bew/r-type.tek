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

    document << u8"doubleKey" << 42.42;

    const std::vector<unsigned char> &retrievedBuffer = document.getBuffer();
    const std::vector<unsigned char> expectedBuffer = {24, 0, 0, 0,                                   // size of document
                                                       1,                                             // id for double element
                                                       100, 111, 117, 98, 108, 101, 75, 101, 121, 0,  // e_name of the value
                                                       246, 40, 92, 143, 194, 53, 69, 64,             // value of the double
                                                       0};                                            // end of document

    ASSERT_EQ(retrievedBuffer, expectedBuffer);
}

/**
 * Check if the string serialize correctly
 */
TEST(Serialization, String) {
    bson::Document document;

    document << u8"stringKey" << std::string(u8"test");

    const std::vector<unsigned char> &retrievedBuffer = document.getBuffer();
    const std::vector<unsigned char> expectedBuffer = {25, 0, 0, 0,                                   // size of document
                                                       2,                                             // id for string element
                                                       115, 116, 114, 105, 110, 103, 75, 101, 121, 0, // e_name of the value
                                                       5, 0, 0, 0,                                    // size of the string
                                                       116, 101, 115, 116, 0,                         // value of the string
                                                       0};                                            // end of document

    ASSERT_EQ(retrievedBuffer, expectedBuffer);
}

/**
 * Check if the document serialize correctly
 */
TEST(Serialization, Document) {
    bson::Document documentDouble;

    documentDouble << u8"doubleKey" << 42.42;

    const std::vector<unsigned char> &retrievedBufferDouble = documentDouble.getBuffer();


    bson::Document documentString;

    documentString << u8"stringKey" << std::string(u8"test");

    const std::vector<unsigned char> &retrievedBufferString = documentString.getBuffer();


    bson::Document document;

    document << u8"documentDouble" << documentDouble
             << u8"documentString" << documentString;

    const std::vector<unsigned char> &retrievedBuffer = document.getBuffer();
    const std::vector<unsigned char> expectedBuffer = {86, 0, 0, 0,                                                           // size of document
                                                       3,                                                                     // id for document element
                                                       100, 111, 99, 117, 109, 101, 110, 116, 68, 111, 117, 98, 108, 101, 0,  // e_name of the value
                                                       24, 0, 0, 0,                                                           // size of documentDouble
                                                       1,                                                                     // id for double element
                                                       100, 111, 117, 98, 108, 101, 75, 101, 121, 0,                          // e_name of the value
                                                       246, 40, 92, 143, 194, 53, 69, 64,                                     // value of the double
                                                       0,                                                                     // end of documentDouble
                                                       3,                                                                     // id for document element
                                                       100, 111, 99, 117, 109, 101, 110, 116, 83, 116, 114, 105, 110, 103, 0, // e_name of the value
                                                       25, 0, 0, 0,                                                           // size of documentString
                                                       2,                                                                     // id for string element
                                                       115, 116, 114, 105, 110, 103, 75, 101, 121, 0,                         // e_name of the value
                                                       5, 0, 0, 0,                                                            // size of the string
                                                       116, 101, 115, 116, 0,                                                 // value of the string
                                                       0,                                                                     // end of documentString
                                                       0};                                                                    // end of document

    ASSERT_EQ(retrievedBuffer, expectedBuffer);
}

TEST(Serialization, Bool) {
    bson::Document documentTrue;

    documentTrue << u8"boolKey" << true;

    const std::vector<unsigned char> &retrievedBufferTrue = documentTrue.getBuffer();
    const std::vector<unsigned char> expectedBufferTrue = {15, 0, 0, 0,                        // size of document
                                                           8,                                  // id for bool element
                                                           98, 111, 111, 108, 75, 101, 121, 0, // e_name of the value
                                                           1,                                  // value of the bool
                                                           0};                                 // end of document

    ASSERT_EQ(retrievedBufferTrue, expectedBufferTrue);

    bson::Document documentFalse;

    documentFalse << u8"boolKey" << false;

    const std::vector<unsigned char> &retrievedBufferFalse = documentFalse.getBuffer();
    const std::vector<unsigned char> expectedBufferFalse = {15, 0, 0, 0,                        // size of document
                                                            8,                                  // id for bool element
                                                            98, 111, 111, 108, 75, 101, 121, 0, // e_name of the value
                                                            0,                                  // value of the bool
                                                            0};                                 // end of document

    ASSERT_EQ(retrievedBufferFalse, expectedBufferFalse);
}

TEST(Serialization, NullValue) {
    bson::Document document;

    document << u8"nullKey" << nullptr;

    const std::vector<unsigned char> &retrievedBuffer = document.getBuffer();
    const std::vector<unsigned char> expectedBuffer = {14, 0, 0, 0,                         // size of document
                                                       10,                                  // id for null value element
                                                       110, 117, 108, 108, 75, 101, 121, 0, // e_name of the value
                                                       0};                                  // end of document

    ASSERT_EQ(retrievedBuffer, expectedBuffer);
}

TEST(Serialization, Int32) {
    bson::Document document;

    document << u8"int32Key" << (int32_t)42;

    const std::vector<unsigned char> &retrievedBuffer = document.getBuffer();
    const std::vector<unsigned char> expectedBuffer = {19, 0, 0, 0,                            // size of document
                                                       16,                                     // id for int32 element
                                                       105, 110, 116, 51, 50, 75, 101, 121, 0, // e_name of the value
                                                       42, 0, 0, 0,                            // value of the int32
                                                       0};                                     // end of document

    ASSERT_EQ(retrievedBuffer, expectedBuffer);
}