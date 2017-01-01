//
// Created by tookie on 12/14/16.
//

#include <iostream>
#include "TestClientUDP.hpp"
#include "Network/ServerUDP.hh"
#include "Network/SocketException.hh"
#include "gtest/gtest.h"
#include "BSON/Document.hh"

TEST(Network, SingleClientUdp)
{

    try
    {
        std::srand(static_cast<unsigned int>(std::time(0))); // use current time as seed for random generator
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

        std::vector<unsigned char> bufferReceived(login.begin(), login.end());
        bson::Document messageReceived(bufferReceived);

        messageReceived["action"] >> login;
        ASSERT_STREQ("login", login.c_str());

        std::string ok("OK");
        bson::Document messageToSend;

        messageToSend << "action" << ok;

        const std::vector<unsigned char> &bufferToSend = messageToSend.getBuffer();
        std::string messageSerialized(bufferToSend.begin(), bufferToSend.end());

        server.addMessage(server.getConnections().at(0), messageSerialized);
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
        std::srand(static_cast<unsigned int>(std::time(0))); // use current time as seed for random generator
        unsigned short random_variable = std::rand() % 65000 + 2500;

        std::vector<unsigned char> bufferReceived;
        bson::Document messageReceived;
        bson::Document messageToSend;

        std::string ok("OK");
        messageToSend << "action" << ok;

        const std::vector<unsigned char> &bufferToSend = messageToSend.getBuffer();
        std::string messageSerialized(bufferToSend.begin(), bufferToSend.end());

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

        bufferReceived = std::vector<unsigned char>(login.begin(), login.end());
        messageReceived = bson::Document(bufferReceived);

        messageReceived["action"] >> login;
        ASSERT_STREQ("login", login.c_str());

        server.addMessage(server.getConnections().at(0), messageSerialized);
        server.update();
        client0.join();

        client1.launch();

        while (server.getConnections().size() == 1)
            server.update();

//Client 1
        login = "";
        login = server.getMessage(server.getConnections().at(1));

        bufferReceived = std::vector<unsigned char>(login.begin(), login.end());
        messageReceived = bson::Document(bufferReceived);

        messageReceived["action"] >> login;
        ASSERT_STREQ("login", login.c_str());

        server.addMessage(server.getConnections().at(1), messageSerialized);
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
        std::srand(static_cast<unsigned int>(std::time(0))); // use current time as seed for random generator
        unsigned short random_variable = std::rand() % 65000 + 2500;

        std::vector<unsigned char> bufferReceived;
        bson::Document messageReceived;
        bson::Document messageToSend;

        std::string ok("OK");
        messageToSend << "action" << ok;

        const std::vector<unsigned char> &bufferToSend = messageToSend.getBuffer();
        std::string messageSerialized(bufferToSend.begin(), bufferToSend.end());

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

        std::string login;

        login = server.getMessage(server.getConnections().at(0));

        bufferReceived = std::vector<unsigned char>(login.begin(), login.end());
        messageReceived = bson::Document(bufferReceived);

        messageReceived["action"] >> login;
        ASSERT_STREQ("login", login.c_str());

        server.addMessage(server.getConnections().at(0), messageSerialized);
        server.update();
        client0.join();

//Client 1

        client1.launch();

        while (server.getConnections().size() == 1)
            server.update();

        login = server.getMessage(server.getConnections().at(1));

        bufferReceived = std::vector<unsigned char>(login.begin(), login.end());
        messageReceived = bson::Document(bufferReceived);

        messageReceived["action"] >> login;
        ASSERT_STREQ("login", login.c_str());

        server.addMessage(server.getConnections().at(1), messageSerialized);
        server.update();
        client1.join();

//Client 2

        client2.launch();

        while (server.getConnections().size() == 2)
            server.update();

        login = server.getMessage(server.getConnections().at(2));

        bufferReceived = std::vector<unsigned char>(login.begin(), login.end());
        messageReceived = bson::Document(bufferReceived);

        messageReceived["action"] >> login;
        ASSERT_STREQ("login", login.c_str());

        server.addMessage(server.getConnections().at(2), messageSerialized);
        server.update();
        client2.join();

//Client 3

        client3.launch();

        while (server.getConnections().size() == 3)
            server.update();

        login = server.getMessage(server.getConnections().at(3));

        bufferReceived = std::vector<unsigned char>(login.begin(), login.end());
        messageReceived = bson::Document(bufferReceived);

        messageReceived["action"] >> login;
        ASSERT_STREQ("login", login.c_str());

        server.addMessage(server.getConnections().at(3), messageSerialized);
        server.update();
        client3.join();
    }
    catch (network::SocketException &e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (bson::BsonException& e)
    {
        std::cerr << e.what() << std::endl;

    }
}
