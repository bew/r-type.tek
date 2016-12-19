
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
	     * add a component.
	     * @param type the type of the component.
	     * @param comp the component.
	     */
	    template<typename CompoType>
	    void	addComponent(const std::string &type, CompoType *comp)
		{
		    _components[type] = static_cast<Component::AComponent *>(comp);
		}

	private:
	    /**
	     * Map of components of the entity.
	     */
	    std::map<const std::string, Component::AComponent *>	_components;
	};

    }
}
