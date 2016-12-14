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
    std::string id("aComputer01");

    bson::Document header = protocol::createHeader(id, "SomeAction");

    EXPECT_EQ(header["id"].getValueString(), id);
    EXPECT_EQ(header["magic"].getValueInt32(), MAGIC);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "SomeAction");
    EXPECT_EQ(header["version"].getValueString(), VERSION);
}