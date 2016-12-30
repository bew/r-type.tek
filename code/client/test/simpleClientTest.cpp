//
// Created by tookie on 12/30/16.
//

#include <memory>

#include "gtest/gtest.h"

#include "ClientTest.hpp"

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 42403

TEST(SimpleClientTest, LoginSinup)
{
    ClientTest client(SERVER_ADDR, 42403);

    client.init();

    client.testLoginSignup();

}

TEST(SimpleClientTest, UnauthorizedRoomJoin)
{
    ClientTest client(SERVER_ADDR, 42403);

    client.init();

    client.testUnauthorizedRoomJoin();
}

TEST(SimpleClientTest, getAvailableROom)
{
    ClientTest client(SERVER_ADDR, 42403);

    client.init();

    client.testGetAvailableRoom();
}

TEST(SimpleClientTest, joinRoom)
{
    ClientTest client(SERVER_ADDR, 42403);

    client.init();

    client.testJoinRoom();
}