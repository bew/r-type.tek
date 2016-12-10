/**
 * @file WorldPools.cpp
 * @brief Implementation of an encapsulation of all the generic object pools.
 * @author Alexis Mongin
 *
 */

#include "WorldPools.hh"

namespace ECS {

    namespace Pools {

	WorldPools::WorldPools()
	    : _entityPool(ObjectPool<Entity::Entity, CommonFactory<Entity::Entity>>(NB_BASE_ELEM, *this))
	{
	}

	WorldPools::~WorldPools()
	{
	}

	void	WorldPools::operator>>(Entity::Entity *&obj)
	{
	    _entityPool >> obj;
	}

	void	WorldPools::operator<<(Entity::Entity *&obj)
	{
	    _entityPool << obj;
	}
	
    }
}
