/**
 * @file CompLife.hh
 * @author Tookie
 * @brief Component implementing the life for game entities.
 *
 */


#pragma once

#include "AComponent.hh"

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
        static const std::string LIFE = "life";

        /**
         * class that represents entites life.
         */
        class CompLife: public AComponent
        {
        public:
            /**
             * Constructor of component life
             * @param maxLife max life of the entity
             */
            CompLife(unsigned int maxLife);

            /**
             *
             * Constructor of component life
             * @param maxLife max life of the entity
             * @param currentLife current life of the entity
             */
            CompLife(unsigned int maxLife, unsigned int currentLife);


            /**
             * Destructor of component life
             */
            ~CompLife();

            /**
             * getter for current life
             * @return the current life of the entity
             */
            unsigned int getCurrentLife() const;

            /**
             * setter for current life
             * @param life is the new value of current life
             */
            void setCurrentLife(unsigned int life);

        private:
            /**
             * Current life of the entity
             */
            unsigned int _currentLife;

            /**
             * max life of the entity
             */
            const unsigned int MAX_LIFE;
        };

    }

}