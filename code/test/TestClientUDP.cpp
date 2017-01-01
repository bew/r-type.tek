//
// Created by tookie on 12/14/16.
//

#include "TestClientUDP.hpp"
#include "gtest/gtest.h"
#include "BSON/Document.hh"

ATask::LockGuard::LockGuard(std::mutex &mutex) : _mutex(mutex)
{
    _mutex.lock();
}

ATask::LockGuard::~LockGuard()
{
    _mutex.unlock();
}

ATask::ATask() : _thread(), _mutex(), _done(false)
{}

void ATask::launch()
{
    _thread = std::thread([this]
                          { this->execLoop(); });
}

void ATask::detach()
{
    _thread.detach();
}

void ATask::join()
{
    _thread.join();
}


bool ATask::isDone() const
{
    return _done;
}

ClientUDP::ClientUDP(const network::SockAddr& serverInfos) : ATask(), _client(serverInfos)
{
}


void ClientUDP::execLoop()
{
    bson::Document messageToSend;

    std::string login("login");

    messageToSend << "action" << login;

    const std::vector<unsigned char>& bufferToSend = messageToSend.getBuffer();
    std::string messageSerialized(bufferToSend.begin(), bufferToSend.end());

    _client.addMessage(messageSerialized);

    _client.update();

    std::string ok = "";

    while ((ok = _client.getMessage()) == "")
        _client.update();

    std::vector<unsigned char> bufferReceived(ok.begin(), ok.end());
    bson::Document messageReceived(bufferReceived);
    ok.clear();

    messageReceived["action"] >> ok;

    ASSERT_STREQ("OK", ok.c_str());
}
