
/**
 * @file World.cpp
 * @author Alexis
 * @brief This class implement the whole world of the R-Type !
 */

#include "World.hh"
 #include "WorldPools.hh"

namespace ECS {

    WorldData::WorldData(Pools::WorldPools &pools)
    	: _packetsRead(), _packetsToWrite(), _gameEntities(), _systemEntity(pools)
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

    void	World::update()
    {
    }

}
