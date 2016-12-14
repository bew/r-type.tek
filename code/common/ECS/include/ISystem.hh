
/**
 * @file ISystem.hh
 * @author Alexis
 * @brief Interface for the different systems.
 */

#pragma once

#include "WorldPools.hh"

/**
 * Namespace of ECS.
 */
namespace ECS {

    /**
     * Declaration of WorldData struct of World.hh.
     * Here in order to avoid a forward declaration of header include.
     */
    struct WorldData;

    /**
     * Namespace of systems.
     */
    namespace System {

	/**
	 * Interface for manipulating the systems.
	 */
	class ISystem
	{
	public:
	    /**
	     * virtual destructor.
	     */
	    virtual ~ISystem() {}

	    /**
	     * Update the world using the system logic.
	     * @param data The persistent information of the ECS.
	     * @param pools The pools for getting/freeing objects.
	     */
	    virtual void	update(WorldData &data, Pools::WorldPools &pools) = 0;
	};

    }
}
