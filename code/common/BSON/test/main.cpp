/**
 * @file main.cpp
 * @brief Main test file
 * @author Christopher Paccard
 *
 * Launch all test files
 *
 */
#include <gtest/gtest.h>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}