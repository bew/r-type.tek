
/**
 * @file AComponent.hh
 * @author Alexis.
 * @brief This abstract class is destinated to manipulate the components.
 *
 */

#pragma once

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
	 * Component types.
	 */
	enum ComponentType : unsigned char
	{
	    NONE = 0,
	    TEST,
	    TYPE,
	    SPRITE,
	    LIFE,
	    MOVEMENT,
	    SHOOT,
	    NETWORK,
	    GRAPHX,
	};

        /**
	 * Abstract class for components.
	 */
	class AComponent
	{
	public:
	    AComponent(ComponentType type);

	    /**
	     * Virtual destructor.
	     */
	    virtual ~AComponent();

	    /**
	     * Getter for the component type.
	     * @return the component type.
	     */
	    ComponentType	getType() const;

	protected:
	    /**
	     * Type of the component.
	     */
	    const ComponentType	_type;
	};

    }
}
