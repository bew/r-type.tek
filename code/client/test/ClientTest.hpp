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

    void init();

    void testLoginSignup();

    void testUnauthorizedRoomJoin();

    void testGetAvailableRoom();

    void testJoinRoom();

    void testGameStart();

private:
    void initStateMachine();
    void initLogLevels() const;

    void checkHeader() const;
    void checkAnswer(int codeExpected) const;
    void checkAvailableRoom() const;
    void checkJoinRoom() const;
    void checkGameStart() const;

    ECS::World _world;
    ECS::Component::CompNetworkClient* _networkClient;
    ECS::Component::CompStateMachine *_stateMachine;
    std::string _username;

};
