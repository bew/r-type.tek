/**
 * @file main.cpp
 * @brief Main test file
 * @author Christopher Paccard
 *
 * Launch all test files
 *
 */

#include <gtest/gtest.h>
#include "Logger.hh"
#include "InfoLogLevel.hh"
#include "ErrorLogLevel.hh"

TEST(Logger, a) {
    logs::logger.logLevel(logs::INFO) << "Yo" << std::endl;
    logs::logger.logLevel(logs::ERROR) << "Yo" << std::endl;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}