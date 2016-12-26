/**
 * @file protocol.cpp
 * @brief protocol test file
 * @author Christopher Paccard
 *
 * Contain all the the test to check protocol
 *
 */

#include <gtest/gtest.h>
#include "Protocol.hh"

/**
 * Basic test to check the header
 */
TEST(Protocol, basic) {
    bson::Document header = protocol::createHeader("SomeAction");

    EXPECT_EQ(header["magic"].getValueInt32(), protocol::magic);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "SomeAction");
    EXPECT_EQ(header["version"].getValueString(), protocol::version);

    EXPECT_EQ(protocol::checkHeader(header, "SomeAction"), true);
}