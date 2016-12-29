/**
 * @file CompLife.hh
 * @author Tookie
 * @brief Component implementing the life for game entities.
 */

#pragma once

#include "AComponent.hh"
#include "Logs/Logger.hh"

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
         * class that represents entities life.
         */
        class CompLife : public AComponent
        {
        public:

            /**
             * Constructor of component life
             * @param maxLife max life of the entity
             * @param currentLife current life of the entity
	     * @param postDamageInvincibility Number of tick between possible alteration of life
             */
	  CompLife(unsigned int maxLife, int postDamageInvincibility = 0);

            /**
             * Destructor of component life
             */
            ~CompLife();

	  /**
	   * @return Current life
	   */
	  int getCurrentLife(void) const;

	  /**
	   * @param The new current life
	   * @param The current tick
	   * @return True if the new life was applied, else false
	   */
	  bool setCurrentLife(int currentLife, int currentTick);

	  /**
	   * Number of tick between possible alteration of life
	   */
	  int postDamageInvincibility;
	  
	  /**
	   * Last tick at which entity got damaged.
	   * -1 if unkown
	   */
	  int lastDamageTick;

            /**
             * get the type of component
             * @return string that reprents his type
             */
            virtual const std::string	&getType() const;

        public:
            /**
             * Current life of the entity
             */
            int _currentLife;

            /**
             * max life of the entity
             */
            const unsigned int _maxLife;
        };

    }
}
