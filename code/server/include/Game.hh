/**
 * @file Game.hh
 * @author Christopher Paccard
 * @brief Class to handle the game
 */

#pragma once

#include <vector>
#include <string>

class Game;

#include "Concurrency/ATask.hh"
#include "Network/ServerUDP.hh"
#include "ECS/World.hh"

#include "Room.hpp"

/**
 * Class that will handle the all game when game is started
 */
class Game : public concurrency::ATask {
private:
    /**
     * Generator's name to use
     */
    std::string _generatorName;

    /**
     * Port to use for the UDP connection
     */
    int32_t _port;

    /**
     * Store the server token that need to match for all the UDP request
     */
    std::string _serverToken;

    /**
     * Store the tokens of the client of the game
     */
     std::vector<std::string> _clientTokens;

    /**
     * World of the game
     */
    ECS::World _world;
public:
    /**
     * Ctor
     *
     * @param generatorName the generator's name to use
     * @param port the port to use for the UDP connection
     * @param serverToken that need to match for all the UDP request
     * @param clientTokens the tokens of the clients of the game
     */
    Game(const std::string& generatorName, int32_t port, const std::string& serverToken, const std::vector<std::string>& clientTokens);

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