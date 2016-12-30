//
// Created by tookie on 12/30/16.
//

#include "ClientTest.hpp"
#include "gtest/gtest.h"
#include "Protocol/Client.hh"
#include "ECS/ECSLogLevel.hh"

ClientTest::ClientTest(const std::string &ip, unsigned short port) :
    _world(), _networkClient(new ECS::Component::CompNetworkClient(ip, port)),
    _stateMachine(new ECS::Component::CompStateMachine)
{

}

ClientTest::~ClientTest()
{

}

void ClientTest::init()
{
    _world._world._systemEntity.addComponent(_networkClient);
    initLogLevels();
    initStateMachine();
}

void ClientTest::initStateMachine()
{
    std::shared_ptr<state_machine::State<std::string>> sAuth = std::make_shared<state_machine::State<std::string>>(
        "s_auth");
    std::shared_ptr<state_machine::State<std::string>> sMenu = std::make_shared<state_machine::State<std::string>>(
        "s_menu");
    std::shared_ptr<state_machine::State<std::string>> sRoom = std::make_shared<state_machine::State<std::string>>(
        "s_room_wait");
    std::shared_ptr<state_machine::State<std::string>> sGame = std::make_shared<state_machine::State<std::string>>(
        "s_game");

    sAuth->addLink("login", sMenu->getName());
    sAuth->addLink("signup", sAuth->getName());

    sMenu->addLink("roomJoin", sRoom->getName());
    sMenu->addLink("logout", sAuth->getName());

    sRoom->addLink("roomKick", sMenu->getName());
    sRoom->addLink("gameStart", sGame->getName());

    sGame->addLink("gameLeave", sMenu->getName());
    sGame->addLink("logout", sAuth->getName());

    _stateMachine->_sm.addState(sAuth);
    _stateMachine->_sm.addState(sMenu);
    _stateMachine->_sm.addState(sRoom);
    _stateMachine->_sm.addState(sGame);

    _stateMachine->_currentState = sAuth->getName();
    _stateMachine->_nextState = sAuth->getName();

    _world._world._systemEntity.addComponent(_stateMachine);
    _world.addSystem(new ECS::System::SysStateMachine);

}

void ClientTest::testLoginSignup()
{
    std::cout << "signup:" << std::endl << "username: ";

    std::cin >> _username;

    std::cout << "password: ";

    std::string pwd;
    std::cin >> pwd;

    std::cout << "signup with username: " << _username << " & password: " << pwd << std::endl;

    _networkClient->_clientTCP.addMessage(protocol::client::signUp(_username, pwd).getBufferString() + network::magic);

    _world.update();

    while (!_networkClient->_clientTCP.hasMessage())
        _networkClient->_clientTCP.update();

    _world.update();

    checkHeader();

    checkAnswer(200);

    ASSERT_EQ("s_auth", _stateMachine->_currentState);

    std::cout << "login:" << std::endl << "username: ";

    std::cin >> _username;

    std::cout << "password: ";

    std::cin >> pwd;

    std::cout << "login with username: " << _username << " & password: " << pwd << std::endl;

    _stateMachine->_nextState = "s_menu";

    _networkClient->_clientTCP.addMessage(protocol::client::login(_username, pwd).getBufferString() + network::magic);

    _world.update();

    while (!_networkClient->_clientTCP.hasMessage())
        _networkClient->_clientTCP.update();

    _world.update();

    checkHeader();

    checkAnswer(200);

    ASSERT_EQ("s_menu", _stateMachine->_currentState);
}

void ClientTest::initLogLevels() const
{
    logs::logger.registerBasicsLogLevel();
    logs::logger.registerLogLevel(&logs::ecsLogLevel);
}

void ClientTest::testUnauthorizedRoomJoin()
{
    bson::Document roomJoin(protocol::client::roomJoin("tookie"));

    std::string msg(roomJoin.getBufferString() + network::magic);

    _networkClient->_clientTCP.addMessage(msg);

    while (!_networkClient->_clientTCP.hasMessage())
        _networkClient->_clientTCP.update();

    _world.update();

    checkHeader();

    checkAnswer(403);
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
    testLoginSignup();

    _stateMachine->_nextState = "s_menu";

    _networkClient->_clientTCP.addMessage(protocol::client::getAvailableRooms().getBufferString() + network::magic);

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

    std::cout << _networkClient->_lastReceived["data"]["data"].getValueDocument().toJSON() << std::endl;
}

void ClientTest::testJoinRoom()
{
    testGetAvailableRoom();

    _networkClient->_clientTCP.addMessage(
        protocol::client::roomJoin("Fast rush, fat pl, no noob").getBufferString() + network::magic);

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
    ASSERT_EQ(_networkClient->_lastReceived["data"]["data"].getValueType(), bson::DOCUMENT);

    std::cout << _networkClient->_lastReceived["data"]["data"].getValueDocument().toJSON() << std::endl;

    ASSERT_EQ(_networkClient->_lastReceived["data"]["players"].getValueType(), bson::DOCUMENT);

    std::cout << _networkClient->_lastReceived["data"]["players"].getValueDocument().toJSON() << std::endl;
}

void ClientTest::testGameStart()
{
    testJoinRoom();

    if (!_networkClient->_lastReceived["data"]["data"].getValueDocument().isEmpty()
        && _networkClient->_lastReceived["data"]["data"].getValueDocument().hasKey("0")
        && _networkClient->_lastReceived["data"]["data"]["0"].getValueType() == bson::STRING)
    {
        _networkClient->_clientTCP.addMessage(protocol::client::gameStart(
            _networkClient->_lastReceived["data"]["data"]["0"].getValueString()).getBufferString() + network::magic);

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
        _networkClient->_clientTCP.addMessage(protocol::client::gameStart("A").getBufferString() + network::magic);
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

    _networkClient->_clientTCP.addMessage(protocol::client::roomLeave().getBufferString() + network::magic);

    _world.update();

    while (!_networkClient->_clientTCP.hasMessage())
        _networkClient->_clientTCP.update();

    _stateMachine->_nextState = "s_menu";

    _world.update();

    checkHeader();

    checkAnswer(200);

    ASSERT_EQ("s_menu", _stateMachine->_currentState);
}


