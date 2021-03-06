
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

	  CompHitbox(void);
	  
	    /**
	     * Constructor
	     * @param mid_width Half the width of the hitbox.
	     * @param mid_height Half the height of the hitbox.
	     */
	    CompHitbox(int mid_width, int mid_height);
	    /**
	     * Destructor
	     */
	    ~CompHitbox();

		/**
         * @return a document describing the component state
         */
		virtual bson::Document serialize() const;

		/**
         * @param document State to write into the component
         */
		virtual void deserialize(const bson::Document& document);

	  /**
	   * @return A pointer to a new CompHitbox with a state similar to this
	   */
	  virtual AComponent *clone(void) const;

            /**
             * get the type of component
             * @return string that reprents his type
             */
            virtual const std::string	&getType() const;

	    /**
	     * Half the width of the hitbox.
	     */
	    int _midWidth;
	    /**
	     * Half the height of the hitbox.
	     */
	    int	_midHeight;
	};

    }
}
