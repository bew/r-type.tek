//
// Created by tookie on 12/30/16.
//

#include <memory>

#include "gtest/gtest.h"

#include "ClientTest.hpp"

TEST(SimpleClientTest, LoginSinup)
{
    ClientTest client("10.41.175.111", 42402);

    client.init();

    client.testLoginSignup();

}

TEST(SimpleClientTest, UnauthorizedRoomJoin)
{
    ClientTest client("10.41.175.111", 42402);

    client.init();

    client.testUnauthorizedRoomJoin();
}