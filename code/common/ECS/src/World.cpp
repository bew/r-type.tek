
/**
 * @file World.cpp
 * @author Alexis
 * @brief This class implement the whole world of the R-Type !
 */

#include "World.hh"
#include "SystemTest.hh"
#include "ComponentTest.hh"

namespace ECS {

    WorldData::WorldData()
    	: _gameEntities(), _systemEntity()
    {}

    WorldData::~WorldData()
    {}

    World::World()
	: _systems(), _world()
    {
    }

    World::~World()
    {
    }

    void	World::initTestSystem()
    {
	System::ISystem	*systemTest = new System::SystemTest(); 
	_systems.push_back(systemTest);
    }

    
    void	World::addTestEntity()
    {
	Entity::Entity	*testEntity = new Entity::Entity();
	Component::ComponentTest *testComponent = new Component::ComponentTest();

	testEntity->addComponent<Component::ComponentTest>(Component::TEST, testComponent);
	_world._gameEntities.push_back(testEntity);
    }

    void	World::update()
    {
	for (auto &e : _systems)
	    e->update(_world);
    }

}
