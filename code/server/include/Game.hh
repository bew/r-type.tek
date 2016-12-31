/**
 * @file Game.hh
 * @author Christopher Paccard
 * @brief Class to handle the game
 */

#pragma once

#include "Concurrency/ATask.hh"
#include "ECS/World.hh"
#include "Network/ServerUDP.hh"

/**
 * Class that will handle the all game when game is started
 */
class Game : public ATask {
private:
    /**
     * Store the server token that need to match for all the UDP request
     */
    std::string _serverToken;

    /**
     * UDP server that will handle the game
     */
    network::ServerUDP _server;

    /**
     * World of the game
     */
    ECS::World _world;
public:
    /**
     * Ctor
     *
     * @param port the port to use for the UDP connection
     * @param serverToken that need to match for all the UDP request
     */
    Game(int32_t port, const std::string& serverToken);

    Game(const Game& game) = delete;

    Game& operator=(const Game& game) = delete;

    /**
     * Dtor
     */
    virtual ~Game();

    /**
     * Function calls by launch method, his execution is in the thread attribute
     */
    virtual void execLoop(void);
};