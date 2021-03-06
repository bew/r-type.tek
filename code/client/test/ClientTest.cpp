//
// Created by tookie on 12/30/16.
//

#include "ClientTest.hpp"
#include "gtest/gtest.h"
#include "Protocol/Client.hh"
#include "ECS/ECSLogLevel.hh"

ClientTest::ClientTest(const std::string &ip, unsigned short port, const std::string &username,
                       const std::string &password) :
    _world(), _networkClient(new ECS::Component::CompNetworkClient()),
    _stateMachine(new ECS::Component::CompStateMachine), _username(username), _password(password)
{

}

ClientTest::~ClientTest()
{

}

void ClientTest::init()
{
    _world._world._systemEntity.addComponent(_networkClient);
    initLogLevels();
    _world._world._systemEntity.addComponent(_stateMachine);
    _world.addSystem(new ECS::System::SysStateMachine);
    _networkClient->_clientTCP.connect(_networkClient->_clientUDP->getAddr());
}

void ClientTest::testSignup()
{
    std::cout << "signup with username: " << _username << " & password: " << _password << std::endl;

    _networkClient->_clientTCP.addMessage(
        protocol::client::signUp(_username, _password).getBufferString());

    _world.update();

    while (!_networkClient->_clientTCP.hasMessage())
        _networkClient->_clientTCP.update();

    _world.update();

    checkHeader();

    checkAnswer(200);

    ASSERT_EQ("s_auth", _stateMachine->_currentState);

}

void ClientTest::testBadLogin()
{
    _stateMachine->_nextState = "s_auth";

    _networkClient->_clientTCP.addMessage(
        protocol::client::login("blarp", "").getBufferString());

    _world.update();

    while (!_networkClient->_clientTCP.hasMessage())
        _networkClient->_clientTCP.update();

    _world.update();

    checkHeader();

    checkAnswer(400);

    ASSERT_EQ("s_auth", _stateMachine->_currentState);
}


void ClientTest::testLogin()
{
    std::cout << "login with username: " << _username << " & password: " << _password << std::endl;

    _stateMachine->_nextState = "s_menu";

    _networkClient->_clientTCP.addMessage(
        protocol::client::login(_username, _password).getBufferString());

    _world.update();

    while (!_networkClient->_clientTCP.hasMessage())
        _networkClient->_clientTCP.update();

    _world.update();

    checkHeader();

    checkAnswer(200);

    ASSERT_EQ("s_menu", _stateMachine->_currentState);
}

void ClientTest::testLoginSignup()
{
    testSignup();

    testLogin();
}

void ClientTest::initLogLevels() const
{
  logs::getLogger().registerBasicsLogLevel();
  logs::getLogger().registerLogLevel(&logs::ecsLogLevel);
}

void ClientTest::testUnauthorizedRoomJoin()
{
    bson::Document roomJoin(protocol::client::roomJoin("tookie"));

    std::string msg(roomJoin.getBufferString());

    _networkClient->_clientTCP.addMessage(msg);

    while (!_networkClient->_clientTCP.hasMessage())
        _networkClient->_clientTCP.update();

    _world.update();

    checkHeader();

    checkAnswer(401);
}

void ClientTest::checkHeader() const
{
    ASSERT_FALSE(_networkClient->_lastReceived.isEmpty());

    ASSERT_TRUE(_networkClient->_lastReceived.hasKey("header"));

    ASSERT_EQ(_networkClient->_lastReceived["header"].getValueType(), bson::DOCUMENT);

    ASSERT_TRUE(_networkClient->_lastReceived["header"].getValueDocument().hasKey("action"));

    ASSERT_EQ(_networkClient->_lastReceived["header"]["action"].getValueType(), bson::STRING);
}

void ClientTest::checkAnswer(int codeExpected) const
{
    ASSERT_EQ(_networkClient->_lastReceived["header"]["action"].getValueString(), "Answer");

    ASSERT_TRUE(_networkClient->_lastReceived.hasKey("data"));

    ASSERT_EQ(_networkClient->_lastReceived["data"].getValueType(), bson::DOCUMENT);

    ASSERT_TRUE(_networkClient->_lastReceived["data"].getValueDocument().hasKey("code"));

    ASSERT_EQ(_networkClient->_lastReceived["data"]["code"].getValueType(), bson::INT32);

    ASSERT_EQ(_networkClient->_lastReceived["data"]["code"].getValueInt32(), codeExpected);
}

void ClientTest::testGetAvailableRoom()
{
    testLogin();

    _stateMachine->_nextState = "s_menu";

    _networkClient->_clientTCP.addMessage(protocol::client::getAvailableRooms().getBufferString());

    _world.update();

    while (!_networkClient->_clientTCP.hasMessage())
        _networkClient->_clientTCP.update();

    _world.update();

    checkHeader();

    checkAnswer(200);

    checkAvailableRoom();

    ASSERT_EQ("s_menu", _stateMachine->_currentState);
}

void ClientTest::checkAvailableRoom() const
{
    ASSERT_EQ(_networkClient->_lastReceived["data"]["data"].getValueType(), bson::DOCUMENT);
}

void ClientTest::testJoinRoom()
{
    testLogin();

    _networkClient->_clientTCP.addMessage(
        protocol::client::roomJoin("Fast rush, fat pl, no noob").getBufferString());

    _stateMachine->_nextState = "s_room_wait";

    _world.update();

    while (!_networkClient->_clientTCP.hasMessage())
        _networkClient->_clientTCP.update();

    _world.update();

    checkHeader();

    checkAnswer(200);

    checkJoinRoom();

    ASSERT_EQ("s_room_wait", _stateMachine->_currentState);

}

void ClientTest::checkJoinRoom() const
{
    ASSERT_TRUE(_networkClient->_lastReceived["data"].getValueDocument().hasKey("data"));

    ASSERT_EQ(_networkClient->_lastReceived["data"]["data"].getValueType(), bson::DOCUMENT);

    ASSERT_TRUE(_networkClient->_lastReceived["data"]["data"].getValueDocument().hasKey("players"));

    ASSERT_EQ(_networkClient->_lastReceived["data"]["data"]["players"].getValueType(), bson::DOCUMENT);

    ASSERT_TRUE(_networkClient->_lastReceived["data"]["data"].getValueDocument().hasKey("generators"));

    ASSERT_EQ(_networkClient->_lastReceived["data"]["data"]["generators"].getValueType(), bson::DOCUMENT);
}

void ClientTest::testGameStart()
{
    testJoinRoom();

    if (!_networkClient->_lastReceived["data"]["data"].getValueDocument().isEmpty()
        && _networkClient->_lastReceived["data"]["data"].getValueDocument().hasKey("0")
        && _networkClient->_lastReceived["data"]["data"]["0"].getValueType() == bson::STRING)
    {
        _networkClient->_clientTCP.addMessage(protocol::client::gameStart(
            _networkClient->_lastReceived["data"]["data"]["0"].getValueString()).getBufferString());

        _stateMachine->_nextState = "s_game";
        _world.update();

        while (!_networkClient->_clientTCP.hasMessage())
            _networkClient->_clientTCP.update();

        _world.update();

        checkGameStart();

        ASSERT_EQ("s_game", _stateMachine->_currentState);
    }
    else
    {
        _networkClient->_clientTCP.addMessage(protocol::client::gameStart("A").getBufferString());
        _world.update();

        while (!_networkClient->_clientTCP.hasMessage())
            _networkClient->_clientTCP.update();

        _stateMachine->_nextState = "s_game";

        _world.update();

        checkHeader();
        checkAnswer(404);

        ASSERT_EQ("s_wait", _stateMachine->_currentState);
    }
}

void ClientTest::checkGameStart() const
{
    checkHeader();

    checkAnswer(200);
}

void ClientTest::testRoomLeave()
{
    testJoinRoom();

    _networkClient->_clientTCP.addMessage(protocol::client::roomLeave().getBufferString());

    _world.update();

    while (!_networkClient->_clientTCP.hasMessage())
        _networkClient->_clientTCP.update();

    _stateMachine->_nextState = "s_menu";

    _world.update();

    checkHeader();

    checkAnswer(200);

    ASSERT_EQ("s_menu", _stateMachine->_currentState);
}

void ClientTest::testGameLeave()
{
    testGameStart();

    _networkClient->_clientTCP.addMessage(protocol::client::gameLeave().getBufferString());

    _world.update();

    while (!_networkClient->_clientTCP.hasMessage())
        _networkClient->_clientTCP.update();

    _stateMachine->_nextState = "s_menu";

    _world.update();

    checkHeader();

    checkAnswer(200);

    ASSERT_EQ("s_menu", _stateMachine->_currentState);
}

void ClientTest::testLogout()
{
    testLogin();

    std::cout << "logout with username: " << _username << " & password: " << _password << std::endl;

    _networkClient->_clientTCP.addMessage(protocol::client::logout().getBufferString());

    _world.update();

    while (!_networkClient->_clientTCP.hasMessage())
        _networkClient->_clientTCP.update();

    _stateMachine->_nextState = "s_auth";

    _world.update();

//    std::cout << "[test logout]: last received: " << _networkClient->_lastReceived.toJSON() << std::endl;

    checkHeader();

    checkAnswer(200);

    ASSERT_EQ("s_auth", _stateMachine->_currentState);
}


