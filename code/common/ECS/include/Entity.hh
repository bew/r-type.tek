
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
namespace ECS {

    /**
     * Namespace of entities.
     */
    namespace Entity {

        /**
         * The next allocated Entity will have this id.
         */
        static unsigned long   EntityNextId = 0;

	/**
	 * Class implementing an entity.
	 */
	class Entity
	{
	public:
	    /**
	     * Constructor.
	     */
	    Entity();
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
	    Component::AComponent	*getComponent(const std::string &type);

            /**
             * Get the id of the entity.
             * @return the id of the entity.
             */
            unsigned long       getId() const;

            /**
	     * add a component.
	     * @param comp the component.
	     */
            void	addComponent(ECS::Component::AComponent *comp);
	private:
            /**
             * Id of the entity.
             */
            const unsigned long       _id;

            /**
	     * Map of components of the entity.
	     */
	    std::map<const std::string, Component::AComponent *>	_components;
	};

    }
}

