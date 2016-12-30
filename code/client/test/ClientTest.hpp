//
// Created by tookie on 12/30/16.
//


#pragma once

#include "ECS/World.hh"
#include "ECS/CompStateMachine.hh"
#include "ECS/CompNetworkClient.hh"
#include "ECS/SysStateMachine.hh"

class ClientTest
{
public:
    ClientTest(const std::string& ip, unsigned short port);
    ~ClientTest();
private:
    ECS::World _world;
    ECS::Component::CompNetworkClient* _networkClient;

};
