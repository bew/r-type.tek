
/**
 * @file AComponent.hh
 * @author Alexis.
 * @brief This abstract class is destinated to manipulate the components.
 *
 */

#pragma once

#include <string>
#include <map>

/**
 * Namespace of ECS.
 */
namespace ECS {

    /**
     * Namespace of components.
     */
    namespace Component {

    /**
	 * Abstract class for components.
	 */
	class AComponent
	{
	public:
	    /**
	     * Constructor
	     * @param type The type of the component.
	     */
	    AComponent(const std::string &type);

	    /**
	     * Virtual destructor.
	     */
	    virtual ~AComponent();

	    /**
	     * Getter for the component type.
	     * @return the component type.
	     */
	    const std::string	&getType() const;

	protected:
	    /**
	     * Type of the component.
	     */
	    const std::string	_type;
	};

    }
}
