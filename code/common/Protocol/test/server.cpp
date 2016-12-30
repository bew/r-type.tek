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

    EXPECT_EQ(protocol::server::checkRoomJoin(message), true);
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

    EXPECT_EQ(protocol::server::checkRoomLeave(message), true);
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

    EXPECT_EQ(protocol::server::checkRoomKick(message), true);
}

/**
 * Check if the message GameStart build correctly
 */
TEST(Server, GameStart) {
    std::string token("aToken");

    bson::Document message = protocol::server::gameStart(token);

    bson::Document header = message["header"].getValueDocument();
    EXPECT_EQ(header["magic"].getValueInt32(), protocol::magic);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "GameStart");
    EXPECT_EQ(header["version"].getValueString(), protocol::version);

    bson::Document data = message["data"].getValueDocument();
    EXPECT_EQ(data["token"].getValueString(), token);

    EXPECT_EQ(protocol::server::checkGameStart(message), true);
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

    EXPECT_EQ(protocol::server::checkGameLeave(message), true);
}

/**
 * Check if the message EntityUpdate build correctly
 */
TEST(Server, EntityUpdate) {
    int64_t entity_id = 4242;
    bson::Document componentTest;
    bson::Document componentData;
    componentData << "x" << 0;
    componentData << "y" << 10;
    componentTest << "data" << componentData;

    bson::Document components;
    components << "test" << componentTest;

    bson::Document message = protocol::server::entityUpdate(entity_id, components);

    bson::Document header = message["header"].getValueDocument();
    EXPECT_EQ(header["magic"].getValueInt32(), protocol::magic);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "EntityUpdate");
    EXPECT_EQ(header["version"].getValueString(), protocol::version);


    bson::Document data = message["data"].getValueDocument();
    EXPECT_EQ(data["entity_id"].getValueInt64(), entity_id);
    EXPECT_EQ(data["components"]["test"].getValueDocument(), componentTest);

    EXPECT_EQ(protocol::server::checkEntityUpdate(message), true);
}