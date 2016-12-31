
/**
 * @file Entity.hh
 * @author Alexis
 * @brief This class implement the base entity.
 */

#pragma once

#include "AComponent.hh"

#include <map>
#include <vector>

/**
 * Namespace of ECS.
 */
namespace ECS
{

    /**
     * Namespace of entities.
     */
    namespace Entity
    {

        /**
         * Class implementing an entity.
         */
        class Entity
        {
        public:

            Entity(void) = delete;

            /**
             * Constructor.
                 * @param id The id of the entity.
             */
            Entity(int64_t id);

            /**
               * Destructor.
               */
            ~Entity();

            Entity(const Entity &) = delete;

            Entity &operator=(const Entity &) = delete;

            /**
             * Get the entity's component of a given type.
             * @param type The type of component requested.
             * @return The component requested, or a nullptr if it doesn't exist.
             */
            Component::AComponent *getComponent(const std::string &type) const;

            /**
             * Get the id of the entity.
             * @return the id of the entity.
             */
            int64_t getId() const;

            /**
    	     * add a component.
	         * @param comp the component.
	         */
            void addComponent(ECS::Component::AComponent *comp);

	  /**
	   * @return Components
	   */
	  std::map<const std::string, Component::AComponent *> &getComponents(void) const;

        private:
            /**
             * Id of the entity.
             */
            const int64_t _id;

            /**
      	     * Map of components of the entity.
	     */
            std::map<const std::string, Component::AComponent *> _components;
        };

    }
}

