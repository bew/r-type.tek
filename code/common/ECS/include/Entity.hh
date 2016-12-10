
/**
 * @file Entity.hh
 * @author Alexis
 * @brief This class implement the base entity.
 */

#pragma once

#include "WorldPools.hh"
#include "APoolable.hh"
#include "AComponent.hh"

#include <map>

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
	class Entity : public Pools::APoolable
	{
	public:
	    /**
	     * Constructor.
	     */
	    Entity(Pools::WorldPools &pools);
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
	    Component::AComponent	*getComponent(Component::ComponentType type);

	    /**
	     * add a component.
	     * @param type the type of the component.
	     * @param comp the component.
	     */
	    template<typename CompoType>
	    void	addComponent(Component::ComponentType type, CompoType *comp)
		{
		    _component[type] = static_cast<Component::AComponent *>(comp);
		}

	    void	clean() override;
	private:
	    /**
	     * Map of components of the entity.
	     */
	    std::map<Component::ComponentType, Component::AComponent *>	_component;
	};

    }
}
