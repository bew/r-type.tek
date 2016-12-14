
/**
 * @file World.cpp
 * @author Alexis
 * @brief This class implement the whole world of the R-Type !
 */

#include "World.hh"
#include "WorldPools.hh"
#include "SystemTest.hh"
#include "ComponentTest.hh"

namespace ECS {

    WorldData::WorldData(Pools::WorldPools &pools)
    	: _packetsRead(), _packetsToWrite(), _gameEntities(), _systemEntity()
    {}

    WorldData::~WorldData()
    {}

    World::World()
	: _systems(), _pools(), _world(_pools)
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
	Entity::Entity	*testEntity;
	Component::ComponentTest *testComponent;
	
	_pools >> testEntity;
	_pools >> testComponent;
	testEntity->addComponent<Component::ComponentTest>(Component::ComponentType::TEST, testComponent);
	_world._gameEntities.push_back(testEntity);
    }

    void	World::update()
    {
	for (auto &e : _systems)
	    e->update(_world, _pools);
    }

}
