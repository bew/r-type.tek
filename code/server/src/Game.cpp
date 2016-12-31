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

#include "LibraryLoader/CompGenerator.hh"
#include "LibraryLoader/SysGenerator.hh"

Game::Game(Room & room, const std::string& generatorName, const std::string &serverToken, const std::vector<std::string>& clientTokens) :
    _generatorName(generatorName), _serverToken(serverToken), _clientTokens(clientTokens), _room(&room)
{}

Game::~Game() {}

void Game::initECS() {
    // init Network component (TODO: make sure the bind is done, to have a valid unused port)
    // init ECS

    // can throw ? => yes
}

int Game::getServerUdpPort() {
    // return port of UDP server for this game
    // see Server#initNetwork() for exemple
}

int Game::runECS() {
    // run ECS

    // (wait for players first connection ? maybe not needed)
}

void Game::execLoop() {

    // TODO: move this in initECS

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

    ///////////////////////// ADD UNIQUE COMPONENTS TO WORLD

    ECS::Component::CompGenerator *generator = new ECS::Component::CompGenerator();
    ECS::Component::CompBlueprint *blueprints = new ECS::Component::CompBlueprint();
    ECS::Component::CompTick *tick = new ECS::Component::CompTick();
    ECS::Component::CompEvent *event = new ECS::Component::CompEvent();

    try {
        std::shared_ptr<LibraryLoader> module(new LibraryLoader(getGenLibName("./generators", _generatorName)));
        Dependent_ptr <IGenerator, LibraryLoader> generatorRef(module->newInstance(), module);
        generator->generator = generatorRef;
    } catch (const LibraryLoaderException &e) {
        logs::getLogger()[logs::ERRORS] << e.what() << std::endl;
    }
    _world.addSystemEntityComponent(generator);
    _world.addSystemEntityComponent(blueprints);
    //
    _world.addSystemEntityComponent(tick);
    _world.addSystemEntityComponent(event);
    _world.addSystemEntityComponent(new ECS::Component::CompCollision());
    _world.addSystemEntityComponent(new ECS::Component::CompScore(0));

    ///////////////////////// Run the world :)

    // TODO: move this in runECS
    while (!tick->kill) {
        _world.update();
    }

    _done = true;



    // NOTE: in execLoop :
    // -> runECS()
    // -> _done = true
}

std::string Game::getGenLibName(std::string const & folder, std::string const & genName)
{
#ifdef _WIN32
    return folder + '/' + genName + ".dll";
#else
    return folder + "/lib" + genName + ".so";
#endif
}
