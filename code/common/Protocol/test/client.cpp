/**
 * @file client.cpp
 * @brief client test file
 * @author Christopher Paccard
 *
 * Contain all the the test to check client
 *
 */

#include <gtest/gtest.h>
#include "Client.hh"

/**
 * Check if the message SignUp build correctly
 */
TEST(Client, SignUp) {
    std::string username("toto42sh");
    std::string password("secret");

    bson::Document message = protocol::client::signUp(username, password);

    bson::Document header = message["header"].getValueDocument();
    EXPECT_EQ(header["magic"].getValueInt32(), protocol::magic);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "SignUp");
    EXPECT_EQ(header["version"].getValueString(), protocol::version);


    bson::Document data = message["data"].getValueDocument();
    EXPECT_EQ(data["username"].getValueString(), username);
    EXPECT_EQ(data["password"].getValueString(), password);

    EXPECT_EQ(protocol::client::checkSignUp(message), true);
}

/**
 * Check if the message Login build correctly
 */
TEST(Client, Login) {
    std::string username("toto42sh");
    std::string password("secret");

    bson::Document message = protocol::client::login(username, password);

    bson::Document header = message["header"].getValueDocument();
    EXPECT_EQ(header["magic"].getValueInt32(), protocol::magic);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "Login");
    EXPECT_EQ(header["version"].getValueString(), protocol::version);


    bson::Document data = message["data"].getValueDocument();
    EXPECT_EQ(data["username"].getValueString(), username);
    EXPECT_EQ(data["password"].getValueString(), password);

    EXPECT_EQ(protocol::client::checkLogin(message), true);
}

/**
 * Check if the message Logout build correctly
 */
TEST(Client, Logout) {
    bson::Document message = protocol::client::logout();

    bson::Document header = message["header"].getValueDocument();
    EXPECT_EQ(header["magic"].getValueInt32(), protocol::magic);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "Logout");
    EXPECT_EQ(header["version"].getValueString(), protocol::version);


    bson::Document data = message["data"].getValueDocument();
    EXPECT_EQ(data.isEmpty(), true);

    EXPECT_EQ(protocol::client::checkLogout(message), true);
}

/**
 * Check if the message RoomJoin build correctly
 */
TEST(Client, RoomJoin) {
    std::string name("toto42sh");
    std::string password("secret");

    bson::Document message = protocol::client::roomJoin(name, password);

    bson::Document header = message["header"].getValueDocument();
    EXPECT_EQ(header["magic"].getValueInt32(), protocol::magic);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "RoomJoin");
    EXPECT_EQ(header["version"].getValueString(), protocol::version);


    bson::Document data = message["data"].getValueDocument();
    EXPECT_EQ(data["name"].getValueString(), name);
    EXPECT_EQ(data["password"].getValueString(), password);


    EXPECT_EQ(protocol::client::checkRoomJoin(message), true);
}

/**
 * Check if the message RoomLeave build correctly
 */
TEST(Client, RoomLeave) {
    bson::Document message = protocol::client::roomLeave();

    bson::Document header = message["header"].getValueDocument();
    EXPECT_EQ(header["magic"].getValueInt32(), protocol::magic);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "RoomLeave");
    EXPECT_EQ(header["version"].getValueString(), protocol::version);

    bson::Document data = message["data"].getValueDocument();
    EXPECT_EQ(data.isEmpty(), true);

    EXPECT_EQ(protocol::client::checkRoomLeave(message), true);
}

/**
 * Check if the message RoomKick build correctly
 */
TEST(Client, RoomKick) {
    std::string username("toto42sh");

    bson::Document message = protocol::client::roomKick(username);

    bson::Document header = message["header"].getValueDocument();
    EXPECT_EQ(header["magic"].getValueInt32(), protocol::magic);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "RoomKick");
    EXPECT_EQ(header["version"].getValueString(), protocol::version);


    bson::Document data = message["data"].getValueDocument();
    EXPECT_EQ(data["username"].getValueString(), username);

    EXPECT_EQ(protocol::client::checkRoomKick(message), true);
}

/**
 * Check if the message GameStart build correctly
 */
TEST(Client, GameStart) {
    bson::Document message = protocol::client::gameStart();

    bson::Document header = message["header"].getValueDocument();
    EXPECT_EQ(header["magic"].getValueInt32(), protocol::magic);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "GameStart");
    EXPECT_EQ(header["version"].getValueString(), protocol::version);

    bson::Document data = message["data"].getValueDocument();
    EXPECT_EQ(data.isEmpty(), true);

    EXPECT_EQ(protocol::client::checkGameStart(message), true);
}

/**
 * Check if the message GameLeave build correctly
 */
TEST(Client, GameLeave) {
    bson::Document message = protocol::client::gameLeave();

    bson::Document header = message["header"].getValueDocument();
    EXPECT_EQ(header["magic"].getValueInt32(), protocol::magic);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "GameLeave");
    EXPECT_EQ(header["version"].getValueString(), protocol::version);


    bson::Document data = message["data"].getValueDocument();
    EXPECT_EQ(data.isEmpty(), true);

    EXPECT_EQ(protocol::client::checkGameLeave(message), true);
}

/**
 * Check if the message EntityUpdate build correctly
 */
TEST(Client, EntityUpdate) {
    int64_t entity_id = 4242;
    bson::Document componentTest;
    bson::Document componentData;
    componentData << "x" << 0;
    componentData << "y" << 10;
    componentTest << "data" << componentData;

    bson::Document components;
    components << "test" << componentTest;

    bson::Document message = protocol::client::entityUpdate(entity_id, components);

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