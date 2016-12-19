
/**
 * @file CompHitbox.hh
 * @author Alexis.
 * @brief This component implement the hitboxes of game entities.
 * The coordinates of the entity, given by the movement component, is the center
 * of the hitbox. As such, we give half the width and half the height of the hitbox.
 * The limits of the hitbox are theses values, mesured from the center.
 */

#pragma once

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
	 * Component type id.
	 */
	static const std::string HITBOX = "hitbox";
	
        /**
	 * Hitboxes of game entites.
	 */
	class CompHitbox : public AComponent
	{
	public:
	    /**
	     * Constructor
	     * @param mid_width Half the width of the hitbox.
	     * @param mid_height Half the height of the hitbox.
	     */
	    CompHitbox(unsigned mid_width, unsigned mid_height);
	    /**
	     * Destructor
	     */
	    ~CompHitbox();

	    /**
	     * Return half the width of the hitbox.
	     * @return half the width of the hitbox.
	     */
	    unsigned	getMidWidth() const;
	    /**
	     * Return half the height of the hitbox.
	     * @return half the height of the hitbox.
	     */
	    unsigned	getMidHeight() const;
	    
	protected:
	    /**
	     * Half the width of the hitbox.
	     */
	    unsigned	_midWidth;
	    /**
	     * Half the height of the hitbox.
	     */
	    unsigned	_midHeight;
	};

    }
}
