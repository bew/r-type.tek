//
// Created by tookie on 12/14/16.
//

#include <iostream>
#include "TestClientUDP.hpp"
#include "ServerUDP.hpp"
#include "SocketException.hh"
#include "gtest/gtest.h"
#include "Document.hh"

TEST(Network, SingleClientUdp)
{

    try
    {
        std::srand(std::time(0)); // use current time as seed for random generator
        unsigned short random_variable = std::rand() % 65000 + 2500;

        network::SockAddr clienInfos(random_variable);

        network::SockAddr serverInfos(random_variable, "127.0.0.1");

        network::ServerUDP server;
        ClientUDP client(serverInfos);

        server.bind(clienInfos);

        client.launch();

        std::string login = "";

        while (server.getConnections().size() == 0)
            server.update();

        login = server.getMessage(server.getConnections().at(0));

        ASSERT_STREQ("login", login.c_str());

        std::string ok("OK");
        ok += CR;
        ok += LF;

        server.addMessage(server.getConnections().at(0), ok);
        server.update();

        client.join();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}


TEST(Network, TwoClientUdp)
{
    try
    {
        std::srand(std::time(0)); // use current time as seed for random generator
        unsigned short random_variable = std::rand() % 65000 + 2500;

        network::SockAddr clienInfos(random_variable);
        network::SockAddr serverInfos(random_variable, "127.0.0.1");

        network::ServerUDP server;

        ClientUDP client0(serverInfos);
        ClientUDP client1(serverInfos);

        server.bind(clienInfos);

        client0.launch();

        while (server.getConnections().size() == 0)
            server.update();

        std::string login = "";

// Client 0

        login = server.getMessage(server.getConnections().at(0));

        ASSERT_STREQ("login", login.c_str());

        std::string ok("OK");
        ok += CR;
        ok += LF;

        server.addMessage(server.getConnections().at(0), ok);
        server.update();
        client0.join();

        client1.launch();

        while (server.getConnections().size() == 1)
            server.update();

//Client 1
        login = "";
        login = server.getMessage(server.getConnections().at(1));

        ASSERT_STREQ("login", login.c_str());

        ok = "OK";
        ok += CR;
        ok += LF;

        server.addMessage(server.getConnections().at(1), ok);
        server.update();
        client1.join();
    }
    catch (network::SocketException &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

TEST(Network, FourClientUdp)
{
    try
    {
        std::srand(std::time(0)); // use current time as seed for random generator
        unsigned short random_variable = std::rand() % 65000 + 2500;

        network::SockAddr clienInfos(random_variable);
        network::SockAddr serverInfos(random_variable, "127.0.0.1");

        network::ServerUDP server;

        ClientUDP client0(serverInfos);
        ClientUDP client1(serverInfos);
        ClientUDP client2(serverInfos);
        ClientUDP client3(serverInfos);

        server.bind(clienInfos);

        client0.launch();
// Client 0

        while (server.getConnections().size() == 0)
            server.update();

        std::string login = "";


        login = server.getMessage(server.getConnections().at(0));

        ASSERT_STREQ("login", login.c_str());

        std::string ok("OK");
        ok += CR;
        ok += LF;

        server.addMessage(server.getConnections().at(0), ok);
        server.update();
        client0.join();

//Client 1

        client1.launch();

        while (server.getConnections().size() == 1)
            server.update();

        login = "";
        login = server.getMessage(server.getConnections().at(1));

        ASSERT_STREQ("login", login.c_str());

        ok = "OK";
        ok += CR;
        ok += LF;

        server.addMessage(server.getConnections().at(1), ok);
        server.update();
        client1.join();

//Client 2

        client2.launch();

        while (server.getConnections().size() == 2)
            server.update();

        login = "";
        login = server.getMessage(server.getConnections().at(2));

        ASSERT_STREQ("login", login.c_str());

        ok = "OK";
        ok += CR;
        ok += LF;

        server.addMessage(server.getConnections().at(2), ok);
        server.update();
        client2.join();

//Client 3

        client3.launch();

        while (server.getConnections().size() == 3)
            server.update();

        login = "";
        login = server.getMessage(server.getConnections().at(3));

        ASSERT_STREQ("login", login.c_str());

        ok = "OK";
        ok += CR;
        ok += LF;

        server.addMessage(server.getConnections().at(3), ok);
        server.update();
        client3.join();
    }
    catch (network::SocketException &e)
    {
        std::cerr << e.what() << std::endl;
    }
}
