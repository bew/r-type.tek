/**
 * @file Game.cpp
 * @author Christopher Paccard
 * @brief Class to handle the game
 */

#include "Game.hh"

Game::Game(int32_t port, const std::string &serverToken) :_serverToken(serverToken), _server(port) {}

Game::~Game() {}

void Game::execLoop() {
    _server.


    ////////////////////////// ADD SYSTEMS TO WORLD

    // control time, Has absolut priority over any other system
    world.addSystem(new ECS::System::SysTick());

    while (!tick->kill)
        world.update();
}