/**
 * @file Game.hh
 * @author Christopher Paccard
 * @brief Class to handle the game
 */

#pragma once

#include <vector>
#include <string>

class Game;

#include "LibraryLoader/ALibraryLoader.hh"
#include "LibraryLoader/Dependent_ptr.hpp"

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
    Dependent_ptr<IGenerator, LibraryLoader> _generator;

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

    /**
     * The parent Room which contain this game
     */
    Room * _room;

public:
    /**
     * Ctor
     *
     * @param room The room which contain this game
     * @param generator the generator to use
     * @param serverToken that need to match for all the UDP request
     * @param clientTokens the tokens of the clients of the game
     */
    Game(Room & room, const Dependent_ptr<IGenerator, LibraryLoader>& generator, const std::string& serverToken, const std::vector<std::string>& clientTokens);

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

    /**
     * Init all the ECS
     */
    void initECS();

    /**
     * Launch the loop of the ECS
     */
    void runECS();

    /**
     * Get the port on which the UDP server run
     *
     * @return the port if everything went right, else -1
     */
    short getServerUdpPort();
};
