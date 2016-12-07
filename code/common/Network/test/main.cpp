//
// Created by Tookie on 07/12/2016.
//

#include "gtest/gtest.h"

#include "SocketException.hh"

#ifdef __linux__
#include "SocketLinuxTCP.h"
#include "SocketLinuxUDP.h"
#elif defined _WIN32

#include "SocketWindowsTCP.h"
#include "SocketWindowsUDP.h"

#endif

TEST(Network, SocketTcp) {
    try {
        std::cout << "yo" << std::endl;
        network::ASocketTCP *socketServer = new network::SocketTCP(26130);
        network::ASocketTCP *socketClient = new network::SocketTCP(26130);

        socketServer->bind();

        socketServer->listen();
        socketServer->accept();

        socketClient->connect();

        std::string login = "login" + CR;
        socketClient->add(login);

        socketClient->update();

        socketServer->update();
        login = socketServer->get();

        ASSERT_STREQ("login", login.c_str());
        std::string ok = "OK" + CR;

        socketServer->add(ok);
        socketServer->update();

        socketClient->update();

        ok = socketClient->get();

        ASSERT_STREQ("OK", ok.c_str());

        socketClient->close();
        socketServer->close();
    }
    catch (network::SocketException &e) {
        std::cerr << e.what() << std::endl;
    }
}

int main(int ac, char **av) {
    ::testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
}