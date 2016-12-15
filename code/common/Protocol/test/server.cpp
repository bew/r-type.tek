/**
 * @file server.cpp
 * @brief server test file
 * @author Christopher Paccard
 *
 * Contain all the the test to check server
 *
 */

#include <gtest/gtest.h>
#include "Server.hh"

/**
 * Check if the message RoomJoin build correctly
 */
TEST(Server, RoomJoin) {
    std::string username("toto42sh");

    bson::Document message = protocol::server::roomJoin(username);

    bson::Document header = message["header"].getValueDocument();
    EXPECT_EQ(header["magic"].getValueInt32(), protocol::magic);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "RoomJoin");
    EXPECT_EQ(header["version"].getValueString(), protocol::version);


    bson::Document data = message["data"].getValueDocument();
    EXPECT_EQ(data["username"].getValueString(), username);
}

/**
 * Check if the message RoomLeave build correctly
 */
TEST(Server, RoomLeave) {
    std::string username("toto42sh");

    bson::Document message = protocol::server::roomLeave(username);

    bson::Document header = message["header"].getValueDocument();
    EXPECT_EQ(header["magic"].getValueInt32(), protocol::magic);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "RoomLeave");
    EXPECT_EQ(header["version"].getValueString(), protocol::version);


    bson::Document data = message["data"].getValueDocument();
    EXPECT_EQ(data["username"].getValueString(), username);
}

/**
 * Check if the message RoomKick build correctly
 */
TEST(Server, RoomKick) {
    std::string username("toto42sh");

    bson::Document message = protocol::server::roomKick(username);

    bson::Document header = message["header"].getValueDocument();
    EXPECT_EQ(header["magic"].getValueInt32(), protocol::magic);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "RoomKick");
    EXPECT_EQ(header["version"].getValueString(), protocol::version);


    bson::Document data = message["data"].getValueDocument();
    EXPECT_EQ(data["username"].getValueString(), username);
}

/**
 * Check if the message GameStart build correctly
 */
TEST(Server, GameStart) {
    bson::Document message = protocol::server::gameStart();

    bson::Document header = message["header"].getValueDocument();
    EXPECT_EQ(header["magic"].getValueInt32(), protocol::magic);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "GameStart");
    EXPECT_EQ(header["version"].getValueString(), protocol::version);
}

/**
 * Check if the message GameLeave build correctly
 */
TEST(Server, GameLeave) {
    std::string username("toto42sh");

    bson::Document message = protocol::server::gameLeave(username);

    bson::Document header = message["header"].getValueDocument();
    EXPECT_EQ(header["magic"].getValueInt32(), protocol::magic);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "GameLeave");
    EXPECT_EQ(header["version"].getValueString(), protocol::version);


    bson::Document data = message["data"].getValueDocument();
    EXPECT_EQ(data["username"].getValueString(), username);
}

/**
 * Check if the message RoomLeave build correctly
 */
TEST(Server, EntityUpdate) {
    int64_t entity_id = 4242;
    std::string component("test");
    bson::Document messageData;
    messageData << "x" << 0;
    messageData << "y" << 10;

    bson::Document message = protocol::server::entityUpdate(entity_id, component, messageData);

    bson::Document header = message["header"].getValueDocument();
    EXPECT_EQ(header["magic"].getValueInt32(), protocol::magic);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "EntityUpdate");
    EXPECT_EQ(header["version"].getValueString(), protocol::version);


    bson::Document data = message["data"].getValueDocument();
    EXPECT_EQ(data["entity_id"].getValueInt64(), entity_id);
    EXPECT_EQ(data["component"].getValueString(), component);
    EXPECT_EQ(data["data"].getValueDocument(), messageData);
}