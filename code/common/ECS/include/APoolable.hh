
/**
 * @file APoolable.hh
 * @author Alexis
 * @brief An abstract from which an object must herit to be manipulated by a pool.
 */

#pragma once
#include "WorldPools.hh"

/**
 * Namespace of ECS.
 */
namespace ECS {
    /**
     * Namespace of generic pools.
     */ 
    namespace Pools {

	/**
	 * An ginterface from which an object must herit to be manipulated by a pool.
	 */
	class APoolable
	{
	public:
	    /**
	     * Constructor.
	     * @param pools Ref to the the worldpools.
	     */
	    APoolable(WorldPools &pools);
	    /**
	     * Virtual destructor.
	     */
	    virtual ~APoolable();

	    /**
	     * Reinitialisartion of the object while placed inside a pool.
	     */
	    virtual void	clean() = 0;
	protected:
	    /**
	     * Ref to world pools for managing owned poolable objects during destruction.
	     */
	    WorldPools	&_pools;
	};
    }
}
