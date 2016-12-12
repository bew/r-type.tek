
/**
 * @file APoolable.cpp
 * @author Alexis
 * @brief An abstract from which an object must herit to be manipulated by a pool.
 */

#include "WorldPools.hh"
#include "APoolable.hh"

namespace ECS {
    namespace Pools {

	APoolable::APoolable(WorldPools &pools)
	    : _pools(pools)
	{
	}

	APoolable::~APoolable()
	{
	}
    }
}
