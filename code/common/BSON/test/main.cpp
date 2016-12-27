/**
 * @file main.cpp
 * @brief Main test file
 * @author Christopher Paccard
 *
 * Launch all test files
 *
 */

#include <gtest/gtest.h>
#include "Document.hh"

int main(int argc, char **argv) {
    std::string json = "{\n\t\"number\": 1,\n\t\"toto\": \"tata\"\n}";
    bson::Document doc;

    doc.readFromFile("/tmp/pd", true);

    std::cout << doc.toJSON() << std::endl;
//    ::testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
}