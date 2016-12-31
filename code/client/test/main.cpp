#include "gtest/gtest.h"
#include "ECS/World.hh"
#include "ECS/ECSLogLevel.hh"
#include "ECS/CompStateMachine.hh"
#include "ECS/CompNetworkClient.hh"
#include "ECS/SysStateMachine.hh"
#include "Protocol/Client.hh"

TEST(clientTest, loginSinup)
{
    logs::getLogger().registerBasicsLogLevel();
    logs::getLogger().registerLogLevel(&logs::ecsLogLevel);
    logs::getLogger().registerLogLevel(&logs::ecsLogLevel);

    ECS::World world;
    ECS::Component::CompNetworkClient* networkClient = new ECS::Component::CompNetworkClient("10.41.175.111", 42402);
    world._world._systemEntity.addComponent(networkClient);
    networkClient->_clientTCP.connect(networkClient->_clientUDP.getAddr());
    ECS::Component::CompStateMachine *stateMachine = new ECS::Component::CompStateMachine;
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

    stateMachine->_sm.addState(sAuth);
    stateMachine->_sm.addState(sMenu);
    stateMachine->_sm.addState(sRoom);
    stateMachine->_sm.addState(sGame);

    world._world._systemEntity.addComponent(stateMachine);

    world.addSystem(new ECS::System::SysStateMachine);

    std::cout << "signup:" << std::endl << "username: ";

    std::string username;
    std::cin >> username;

    std::cout << "password: ";

    std::string pwd;
    std::cin >> pwd;

    std::cout << "username: " << username << std::endl;
    std::cout << "password: " << pwd << std::endl;

    bson::Document signup = protocol::client::signUp(username, pwd);

    std::string msg(signup.getBufferString());
    msg +=  network::magic;

    std::cout << msg << std::endl;
    std::cout << signup.toJSON() << std::endl;
    networkClient->_clientTCP.addMessage(msg);
    stateMachine->_nextState = sAuth->getName();

    world.update();

    while (!networkClient->_clientTCP.hasMessage())
        networkClient->_clientTCP.update();

    world.update();

    ASSERT_EQ(sAuth->getName(), stateMachine->_currentState);

    std::cout << "login:" << std::endl << "username: ";

    std::cin >> username;

    std::cout << "password: ";

    std::cin >> pwd;

    std::cout << "username: " << username << std::endl;
    std::cout << "password: " << pwd << std::endl;

    bson::Document login = protocol::client::login(username, pwd);

    stateMachine->_nextState = sMenu->getName();

    msg = login.getBufferString();
    msg +=  network::magic;

    networkClient->_clientTCP.addMessage(msg);

    world.update();

    while (!networkClient->_clientTCP.hasMessage())
        networkClient->_clientTCP.update();

    world.update();

    ASSERT_EQ(sMenu->getName(), stateMachine->_currentState);
}

int main(int ac, char **av)
{
    ::testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
}
