//
// Created by tookie on 12/14/16.
//


#include <iostream>
#include "TestClientTCP.hpp"
#include "ServerTCP.hh"
#include "SocketException.hh"
#include "gtest/gtest.h"
#include "Document.hh"

TEST(Network, SingleClientTcp)
{
    try
    {
        std::srand(static_cast<unsigned int>(std::time(0))); // use current time as seed for random generator
        unsigned short random_variable = std::rand() % 65000 + 2500;
        network::SockAddr clienInfos(random_variable);
        network::SockAddr serverInfos(random_variable, "127.0.0.1");

        std::vector<unsigned char> bufferReceived;
        bson::Document messageReceived;
        bson::Document messageToSend;

        std::string ok("OK");
        messageToSend << "action" << ok;

        const std::vector<unsigned char> &bufferToSend = messageToSend.getBuffer();
        std::string messageSerialized(bufferToSend.begin(), bufferToSend.end());

        messageSerialized += network::CR;
        messageSerialized += network::LF;

        network::ServerTCP server;
        ClientTCP client(serverInfos);

        server.bind(clienInfos);

        server.listen();

        client.launch();

        while (server.getConnections().size() == 0)
            server.update();

        std::string login = "";

        while ((login = server.getMessage(server.getConnections().at(0))).empty())
            server.update();

        bufferReceived = std::vector<unsigned char>(login.begin(), login.end());
        messageReceived = bson::Document(bufferReceived);

        messageReceived["action"] >> login;

        ASSERT_STREQ("login", login.c_str());

        server.addMessage(server.getConnections().at(0), messageSerialized);
        server.update();

        client.join();
    }
    catch (network::SocketException &e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (bson::BsonException &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

TEST(Network, TwoClientTcp)
{
    try
    {
        std::srand(static_cast<unsigned int>(std::time(0))); // use current time as seed for random generator
        unsigned short random_variable = std::rand() % 65000 + 2500;

        network::SockAddr clienInfos(random_variable);
        network::SockAddr serverInfos(random_variable, "127.0.0.1");

        std::vector<unsigned char> bufferReceived;
        bson::Document messageReceived;
        bson::Document messageToSend;

        std::string ok("OK");
        messageToSend << "action" << ok;

        const std::vector<unsigned char> &bufferToSend = messageToSend.getBuffer();
        std::string messageSerialized(bufferToSend.begin(), bufferToSend.end());

        messageSerialized += network::CR;
        messageSerialized += network::LF;

        network::ServerTCP server;

        ClientTCP client0(serverInfos);
        ClientTCP client1(serverInfos);

        server.bind(clienInfos);

        server.listen();

        client0.launch();

        while (server.getConnections().size() == 0)
            server.update();

        std::string login = "";

        // Client 0

        while ((login = server.getMessage(server.getConnections().at(0))).empty())
            server.update();

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
        while ((login = server.getMessage(server.getConnections().at(1))).empty())
            server.update();

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
    catch (bson::BsonException &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

TEST(Network, FourClientTcp)
{
    try
    {
        std::srand(static_cast<unsigned int>(std::time(0))); // use current time as seed for random generator
        unsigned short random_variable = std::rand() % 65000 + 2500;

        network::SockAddr clienInfos(random_variable);
        network::SockAddr serverInfos(random_variable, "127.0.0.1");

        std::vector<unsigned char> bufferReceived;
        bson::Document messageReceived;
        bson::Document messageToSend;

        std::string ok("OK");
        messageToSend << "action" << ok;

        const std::vector<unsigned char> &bufferToSend = messageToSend.getBuffer();
        std::string messageSerialized(bufferToSend.begin(), bufferToSend.end());

        messageSerialized += network::CR;
        messageSerialized += network::LF;

        network::ServerTCP server;

        ClientTCP client0(serverInfos);
        ClientTCP client1(serverInfos);
        ClientTCP client2(serverInfos);
        ClientTCP client3(serverInfos);

        server.bind(clienInfos);

        server.listen();

        client0.launch();
        // Client 0

        while (server.getConnections().size() == 0)
            server.update();

        std::string login = "";

        while ((login = server.getMessage(server.getConnections().at(0))).empty())
            server.update();

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

        login = "";
        while ((login = server.getMessage(server.getConnections().at(1))).empty())
            server.update();


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

        login = "";
        while ((login = server.getMessage(server.getConnections().at(2))).empty())
            server.update();

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

        login = "";
        while ((login = server.getMessage(server.getConnections().at(3))).empty())
            server.update();

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
    catch (bson::BsonException &e)
    {
        std::cerr << e.what() << std::endl;
    }
}
