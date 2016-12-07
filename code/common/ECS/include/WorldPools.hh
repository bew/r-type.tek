
/**
 * @file WorldPools.hh
 * @author Alexis
 * @brief This is an abstraction for the object pool. Putting the ObjectPool template
 * class behind a single compilation dependency will reduce the compile time
 * and simplify the access behind all the pools.
 *
 * Basically, create a pool of the object you need, and the related factory
 * (check ObjectPool.hpp) in ObjPoolFactories.hpp, then overload the << >>
 * operators of the world factory and the type of your object.
 *
 */

#pragma once

#include "ObjPoolFactories.hpp"
#include "Entity.hh"
#include "ObjectPool.hpp"

/**
 * Namespace of ECS.
 */
namespace ECS {

    /**
     * Namespace of the generic pools used to abstract objects allocation.
     */
    namespace Pools {
	
	/**
	 * A class hiding all the object pool. Reduce code complexity and compile time,
	 * since our templated class is only included in this file.
	 */
	class WorldPools
	{
	public:

	    /**
	     * Number of elements built in pools during initialisation.
	     */
	    const unsigned	NB_BASE_ELEM = 600;

	    /**
	     * Constructor.
	     */
	    WorldPools();

	    /**
	     * Destructor.
	     */
	    ~WorldPools();

	    WorldPools(const WorldPools &) = delete;
	    WorldPools &operator=(const WorldPools &) = delete;

	    /**
	     * operator overloading for borrowing an entity.
	     * @param obj The object taken from pool.
	     */
	    void	operator>>(Entity::Entity *&obj);

	    /**
	     * operator overloading for borrowing an entity.
	     * @param obj The object returned in pool.
	     */
	    void	operator<<(Entity::Entity *&obj);
    
	private:
	    /**
	     * Generic pool of entities.
	     */
	    ObjectPool<Entity::Entity, CommonFactory<Entity::Entity>>	_entityPool;
	};
    }
}
