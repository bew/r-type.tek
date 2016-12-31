//
// Created by tookie on 12/30/16.
//


#pragma once

#include "ECS/World.hh"
#include "CompStateMachine.hh"
#include "CompNetworkClient.hh"
#include "SysStateMachine.hh"

class ClientTest
{
public:
    ClientTest(const std::string &ip, unsigned short port, const std::string &username, const std::string &password);

    ~ClientTest();

    void init();

    void testBadLogin();

    void testLoginSignup();

    void testUnauthorizedRoomJoin();

    void testGetAvailableRoom();

    void testJoinRoom();

    void testGameStart();

    void testRoomLeave();

    void testGameLeave();

    void testLogout();

private:
    void initLogLevels() const;

    void testLogin();

    void testSignup();

    void checkHeader() const;

    void checkAnswer(int codeExpected) const;

    void checkAvailableRoom() const;

    void checkJoinRoom() const;

    void checkGameStart() const;

    ECS::World _world;
    ECS::Component::CompNetworkClient *_networkClient;
    ECS::Component::CompStateMachine *_stateMachine;
    std::string _username;
    std::string _password;

};
