
/**
 * @file WorldPools.hh
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
	    AComponent() = delete;

	    /**
	     * Virtual destructor.
	     */
	    virtual ~AComponent() {}

	    AComponent(const AComponent &) = delete;
	    AComponent &operator=(const AComponent &) = delete;

	    /**
	     * Getter for the component type.
	     */
	    virtual ComponentType	getType() const = 0;

	private:

	    /**
	     * Type of the component.
	     */
	    const ComponentType	_type;
	};

    }
}
