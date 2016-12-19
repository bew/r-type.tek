
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
namespace ECS {

    /**
     * Namespace of components.
     */
    namespace Component {

        /**
         * Component type id.
         */
	static const std::string MOVEMENT = "movement";

        /**
         * Abstract class for components.
         */
        class CompMovement : public AComponent
        {
        public:
            /**
             * Constructor.
             */
            CompMovement();
            /**
             * Destructor.
             */
            ~CompMovement();

            enum FacingDirection
            {
                BACKWARD,
                FORWARD
            };

            /**
             * Coordinates of the entity.
             */
            coordinates<int>    _coo;
            /**
             * Vector deplacement of the entity.
             */
            coordinates<float>  _dir;
            /**
             * Speed of the entity.
             */
            float               _speed;
            /**
             * Current advance of the entity for <1 pixel movement.
             */
            coordinates<float>  _advance;
            /**
             * Direction faced by the entiy;
             */
            FacingDirection     _facingDir;
        };

    }
}
