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

TEST(Logger, a) {
    log::logger.logLevel(log::INFO) << "Yo" << std::endl;
    log::logger.logLevel(log::INFO) << "Yo" << std::endl;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}