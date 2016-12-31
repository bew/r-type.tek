/**
 * @file Game.cpp
 * @author Christopher Paccard
 * @brief Class to handle the game
 */

#include "Game.hh"
#include "ECS/SysTick.hh"

Game::Game(const std::string& generatorName, int32_t port, const std::string &serverToken, const std::vector<std::string>& clientTokens) :
    _generatorName(generatorName), _port(port), _serverToken(serverToken), _clientTokens(clientTokens), _done(false), _room(&room)
{}

Game::~Game() {}

void Game::execLoop() {
    // TODO: Get the UDP players

    ////////////////////////// ADD SYSTEMS TO WORLD

    // control time, Has absolut priority over any other system
    _world.addSystem(new ECS::System::SysTick());
    // control time, Has absolut priority over any other system
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

    // TODO: Use _generatorName
    try {
#ifdef _WIN32
        std::shared_ptr<LibraryLoader> module(new LibraryLoader("./generators/fly.dll"));
#else
        std::shared_ptr <LibraryLoader> module(new LibraryLoader("./generators/libfly.so"));
#endif
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

    while (!tick->kill) {
        _world.update();
    }

    _done = true;
}
