/**
 * @file Game.hh
 * @author Christopher Paccard
 * @brief Class to handle the game
 */

#pragma once

#include "Concurrency/ATask.hh"
#include "Network/ServerUDP.hh"

#include "ECS/World.hh"
#include "ECS/CompScore.hh"
#include "ECS/CompMusic.hh"
#include "ECS/CompSprite.hh"
#include "ECS/CompCollision.hh"
#include "ECS/SysController.hh"
#include "ECS/SysCollision.hh"
#include "ECS/CompCollision.hh"
#include "ECS/CompController.hh"
#include "ECS/CompEvent.hh"
#include "ECS/SysEvent.hh"
#include "ECS/CompTick.hh"
#include "ECS/SysTick.hh"
#include "ECS/CompMovement.hh"
#include "ECS/SysMovement.hh"
#include "ECS/SysCollision.hh"
#include "ECS/CompHitbox.hh"
#include "ECS/CompBlueprint.hh"
#include "ECS/CompProjectile.hh"
#include "ECS/CompDamage.hh"
#include "ECS/CompLife.hh"
#include "ECS/SysDeath.hh"
#include "ECS/SysLife.hh"
#include "ECS/SysDamage.hh"
#include "ECS/CompType.hh"
#include "ECS/CompSuccessor.hh"
#include "ECS/SysIA.hh"

#include "LibraryLoader/CompGenerator.hh"
#include "LibraryLoader/SysGenerator.hh"

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
     * @param generatorName the generator's name to use
     * @param port the port to use for the UDP connection
     * @param serverToken that need to match for all the UDP request
     */
    Game(const std::string& generatorName, int32_t port, const std::string& serverToken);

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