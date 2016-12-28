//
// Created by tookie on 12/14/16.
//

//
// Created by tookie on 12/14/16.
//

#include "TestClientTCP.hpp"
#include "gtest/gtest.h"
#include "BSON/Document.hh"

ClientTCP::ClientTCP(const network::SockAddr& serverInfos) : ATask(), _client(), _serverInfos(serverInfos)
{
}


void ClientTCP::execLoop()
{
    bson::Document messageToSend;

    std::string login("login");

    messageToSend << "action" << login;

    const std::vector<unsigned char>& bufferToSend = messageToSend.getBuffer();
    std::string messageSerialized(bufferToSend.begin(), bufferToSend.end());

    _client.connect(_serverInfos);

    messageSerialized += network::CR;
    messageSerialized += network::LF;

    _client.addMessage(messageSerialized);

    _client.update(0);

    std::string ok = "";

    while ((ok = _client.getMessage()) == "")
        _client.update(0);

    std::vector<unsigned char> bufferReceived(ok.begin(), ok.end());
    bson::Document messageReceived(bufferReceived);
    ok.clear();

    messageReceived["action"] >> ok;

    ASSERT_STREQ("OK", ok.c_str());
}
