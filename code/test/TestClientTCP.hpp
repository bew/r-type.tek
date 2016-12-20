//
// Created by tookie on 12/14/16.
//

#pragma once

#include <thread>
#include <mutex>
#include <atomic>
#include "TestClientUDP.hpp"
#include "SockAddr.hh"
#include "ClientTCP.hh"

class ClientTCP : public ATask
{
public:
    ClientTCP(const network::SockAddr &serverInfos);

    ~ClientTCP()
    {};

    virtual void execLoop();

private:
    network::ClientTCP _client;
    network::SockAddr _serverInfos;
};
