
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
	    ISystem() = delete;

	    /**
	     * virtual destructor.
	     */
	    virtual ~ISystem() {}

	    ISystem(const ISystem &) = delete;
	    ISystem &operator=(const ISystem &) = delete;

	    /**
	     * Update the world using the system logic.
	     */
	    virtual void	update(WorldData &, Pools::WorldPools &) = 0;
	};

    }
}
