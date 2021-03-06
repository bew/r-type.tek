/**
 * @file Game.cpp
 * @author Christopher Paccard
 * @brief Class to handle the game
 */

#include "Game.hh"

#include "ECS/CompBlueprint.hh"
#include "ECS/CompCollision.hh"
#include "ECS/CompController.hh"
#include "ECS/CompDamage.hh"
#include "ECS/CompEvent.hh"
#include "ECS/CompHitbox.hh"
#include "ECS/CompLife.hh"
#include "ECS/CompMovement.hh"
#include "ECS/CompMusic.hh"
#include "ECS/CompProjectile.hh"
#include "ECS/CompScore.hh"
#include "ECS/CompSprite.hh"
#include "ECS/CompSuccessor.hh"
#include "ECS/CompTick.hh"
#include "ECS/CompType.hh"
#include "ECS/SysCollision.hh"
#include "ECS/SysController.hh"
#include "ECS/SysDamage.hh"
#include "ECS/SysDeath.hh"
#include "ECS/SysEvent.hh"
#include "ECS/SysIA.hh"
#include "ECS/SysLife.hh"
#include "ECS/SysMovement.hh"
#include "ECS/SysTick.hh"
#include "SysSerialisation.hh"
#include "CompNetworkServer.hh"

#include "LibraryLoader/CompGenerator.hh"
#include "LibraryLoader/SysGenerator.hh"

Game::Game(Room & room, const Dependent_ptr<IGenerator, LibraryLoader>& generator, const std::string &serverToken, const std::vector<std::string>& clientTokens) :
        _room(&room), _generator(generator), _serverToken(serverToken), _clientTokens(clientTokens)
{}

Game::~Game() {}

void Game::initECS() {
    ////////////////////////// ADD SYSTEMS TO WORLD

    // control time, Has absolute priority over any other system
    _world.addSystem(new ECS::System::SysTick());
    // control time, Has absolute priority over any other system
    _world.addSystem(new ECS::System::SysGenerator());
    // transform data to movement (speed, direction)
    _world.addSystem(new ECS::System::SysController());
    // update movement speed, direction for computer controlled entity
    _world.addSystem(new ECS::System::SysIA());
    // transform movement to  movement(position)
    _world.addSystem(new ECS::System::SysMovement());
    // Analyze collision, fill compCollision
    _world.addSystem(new ECS::System::SysCollision());
    // process collision and apply damage
    _world.addSystem(new ECS::System::SysDamage());
    // process life and apply death
    _world.addSystem(new ECS::System::SysLife());
    // process entity and remove the dead ones
    _world.addSystem(new ECS::System::SysDeath());
    // process events that happen in the tick
    _world.addSystem(new ECS::System::SysEvent());
    // process serialization/unserialization of entity
    _world.addSystem(new ECS::System::SysSerialisation);

    ///////////////////////// ADD UNIQUE COMPONENTS TO WORLD

    ECS::Component::CompGenerator *generator = new ECS::Component::CompGenerator();

    generator->generator = _generator;

    _world.addSystemEntityComponent(generator);
    _world.addSystemEntityComponent(new ECS::Component::CompBlueprint());
    _world.addSystemEntityComponent(new ECS::Component::CompTick());
    _world.addSystemEntityComponent(new ECS::Component::CompEvent());
    _world.addSystemEntityComponent(new ECS::Component::CompCollision());
    _world.addSystemEntityComponent(new ECS::Component::CompScore(0));
    _world.addSystemEntityComponent(new ECS::Component::CompNetworkServer(0, _serverToken, _clientTokens));

    size_t playerNumber = 1;
    for (const auto& player : _room->players) {
        _world._world._gameEntities.push_back(new ECS::Entity::Entity(playerNumber));
        ++playerNumber;
    }
}

short Game::getServerUdpPort() {
    ECS::Component::CompNetworkServer *compNetworkServer =
            dynamic_cast<ECS::Component::CompNetworkServer*>(_world._world._systemEntity.getComponent(ECS::Component::NETWORK_SERVER));
    return (compNetworkServer ? compNetworkServer->_port : static_cast<short>(-1));
}

void Game::runECS() {
    ECS::Component::CompTick *compTick = dynamic_cast<ECS::Component::CompTick *>(_world._world._systemEntity.getComponent(ECS::Component::TICK));
    if (compTick) {
        // FIXME: Should it be an error ? Is it possible ?
        while (!compTick->kill) {
            _world.update();
        }
    }
}

void Game::execLoop() {
    this->runECS();
    _done = true;
}
