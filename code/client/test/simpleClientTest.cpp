//
// Created by tookie on 12/30/16.
//

#include "gtest/gtest.h"

#include "ClientTest.hpp"

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 42403

TEST(SimpleClientTest, LoginSinup)
{
    ClientTest client(SERVER_ADDR, SERVER_PORT);

    client.init();

    client.testLoginSignup();

}

TEST(SimpleClientTest, UnauthorizedRoomJoin)
{
    ClientTest client(SERVER_ADDR, SERVER_PORT);

    client.init();

    client.testUnauthorizedRoomJoin();
}

TEST(SimpleClientTest, getAvailableROom)
{
    ClientTest client(SERVER_ADDR, SERVER_PORT);

    client.init();

    client.testGetAvailableRoom();
}

TEST(SimpleClientTest, joinRoom)
{
    ClientTest client(SERVER_ADDR, SERVER_PORT);

    client.init();

    client.testJoinRoom();
}


TEST(SimpleClientTest, RoomLeave)
{
    ClientTest client(SERVER_ADDR, SERVER_PORT);

    client.init();

    client.testRoomLeave();
}

TEST(SimpleClientTest, GameStart)
{
    ClientTest client(SERVER_ADDR, SERVER_PORT);

    client.init();

    client.testGameStart();
}

TEST(SimpleClientTest, GameLeave)
{
    ClientTest client(SERVER_ADDR, SERVER_PORT);

    client.init();

    client.testGameLeave();
}


TEST(SimpleClientTest, Logout)
{
    ClientTest client(SERVER_ADDR, SERVER_PORT);

    client.init();

    client.testLogout();
}