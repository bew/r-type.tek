
/**
 * @file ISystem.hh
 * @author Alexis
 * @brief Interface for the different systems.
 */

#pragma once

/**
 * Namespace of ECS.
 */
namespace ECS {

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
	     */
	    virtual void	update(WorldData &data) = 0;
	};

    }
}
