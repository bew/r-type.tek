
/**
 * @file ComponentTest.hh
 * @author Alexis.
 * @brief Dummy component for testing purposes.
 *
 */

#include "AComponent.hh"


/**
 * Namespace of ECS.
 */
namespace ECS {

    /**
     * Namespace of components.
     */
    namespace Component {

	/**
	 * Dummy component for testing purpose.
	 */
	class ComponentTest : public AComponent
	{
	public:
	    /**
	     * Constructor.
	     */
	    ComponentTest();
	    /**
	     * Destructor.
	     */
	    ~ComponentTest();

	    /**
	     * Add 1 to the count.
	     */
	    void	increment();
	    /**
	     * Return the count.
	     * @return The count.
	     */
	    unsigned	getCount() const;

	private:
	    
	    /**
	     * A dummy data for testing purpose.
	     */
	    unsigned	_count;
	};

    }
}
