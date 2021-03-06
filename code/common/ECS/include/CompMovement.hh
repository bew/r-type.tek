
/**
 * @file CompMovement.hh
 * @author Alexis.
 * @brief Component implementing the movement for game entities.
 *
 */

#pragma once

#include "AComponent.hh"
#include "Coordinates.hh"

/**
 * Namespace of ECS.
 */
namespace ECS
{

    /**
     * Namespace of components.
     */
    namespace Component
    {

        /**
         * Component type id.
         */
        static const std::string MOVEMENT = "movement";

        /**
         * class that represents entites movements.
         */
        class CompMovement : public AComponent
        {
        public:
            /**
             * Constructor.
	     *
	     * @param coop Initial coordonate
	     * @param speed Initial speed
	     * @param dir Initial direction
             */
	  CompMovement(coordinates<int> coor = {0, 0}, float speed = 0, coordinates<float> dir = {0.0, 0.0});

	  /**
	   * Destructor.
	   */
	  ~CompMovement();
	  
	  /**
	   * @return a document describing the component state
	   */
	  virtual bson::Document serialize() const;
	  
	  /**
	   * @param document State to write into the component
	   */
	  virtual void deserialize(const bson::Document& document);
	  


	  /**
	   * @return A pointer to a new CompMevement with a state similar to this
	   */
	  AComponent *clone(void) const;

            /**
             * get the type of component
             * @return string that reprents his type
             */
            virtual const std::string	&getType() const;

            /**
             * Description of the way the sprite should face during
             * graphic rendering depending to the deplacement vector
             * of the entity.
             */
            enum FacingDirection
            {
                BACKWARD,
                FORWARD
            };

            /**
             * Coordinates of the entity.
             */
            coordinates<int> _coo;
            /**
             * Vector deplacement of the entity.
             */
            coordinates<float> _dir;
            /**
             * Speed of the entity.
             */
            float _speed;
            /**
             * Current advance of the entity for <1 pixel movement.
             */
            coordinates<float> _advance;
            /**
             * Direction faced by the entiy;
             */
            FacingDirection _facingDir;
        };

    }
}
