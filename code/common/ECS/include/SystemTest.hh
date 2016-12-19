
/**
 * @file SystemTest.hh
 * @author Alexis.
 * @brief Dummy system for testing purposes.
 *
 */

#pragma once
#include "ISystem.hh"

/**
 * Namespace of ECS.
 */
namespace ECS {

    /**
     * Namespace of systems.
     */
    namespace System {

	/**
	 * Dummy system for testing purposes.
	 */
	class SystemTest : public ISystem
	{
	public:
	    /**
	     * Constructor.
	     */
	    SystemTest();
	    /**
	     * Destructor.
	     */
	    ~SystemTest();

	    /**
	     * update function. Will increment all ComponentTest count by one.
	     * @param data The persistent information of the ECS.
	     */
	    void	update(WorldData &data) override;
	};
    }
}
