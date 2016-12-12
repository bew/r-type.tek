
/**
 * @file SystemTest.hh
 * @author Alexis.
 * @brief Dummy system for testing purposes.
 *
 */

#include "WorldPools.hh"
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
	     * @param pools The pools for getting/freeing objects.
	     */
	    void	update(WorldData &data, Pools::WorldPools &pools) override;
	};
    }
}
