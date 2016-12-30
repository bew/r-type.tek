//
// Created by tookie on 12/30/16.
//

#include "gtest/gtest.h"

#include "ClientTest.hpp"

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 42402
#define USERNAME "tookieg"
#define PASSWORD "lol"

TEST(SimpleClientTest, LoginSinup)
{
    ClientTest client(SERVER_ADDR, SERVER_PORT, USERNAME, PASSWORD);

    client.init();

    client.testLoginSignup();

}

TEST(SimpleClientTest, BadLogin)
{
    ClientTest client(SERVER_ADDR, SERVER_PORT, USERNAME, PASSWORD);

    client.init();

    client.testBadLogin();
}


TEST(SimpleClientTest, UnauthorizedRoomJoin)
{
    ClientTest client(SERVER_ADDR, SERVER_PORT, USERNAME, PASSWORD);

    client.init();

    client.testUnauthorizedRoomJoin();
}

/*TEST(SimpleClientTest, getAvailableROom)
{
    ClientTest client(SERVER_ADDR, SERVER_PORT, USERNAME, PASSWORD);

    client.init();

    client.testGetAvailableRoom();
}
*/

 TEST(SimpleClientTest, joinRoom)
{
    ClientTest client(SERVER_ADDR, SERVER_PORT, USERNAME, PASSWORD);

    client.init();

    client.testJoinRoom();
}

TEST(SimpleClientTest, RoomLeave)
{
    ClientTest client(SERVER_ADDR, SERVER_PORT, USERNAME, PASSWORD);

    client.init();

    client.testRoomLeave();
}
/*
TEST(SimpleClientTest, GameStart)
{
    ClientTest client(SERVER_ADDR, SERVER_PORT, USERNAME, PASSWORD);

    client.init();

    client.testGameStart();
}

TEST(SimpleClientTest, GameLeave)
{
    ClientTest client(SERVER_ADDR, SERVER_PORT, USERNAME, PASSWORD);

    client.init();

    client.testGameLeave();
}


TEST(SimpleClientTest, Logout)
{
    ClientTest client(SERVER_ADDR, SERVER_PORT, USERNAME, PASSWORD);

    client.init();

    client.testLogout();
}
 */