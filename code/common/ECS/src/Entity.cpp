
/**
 * @file Entity.hh
 * @author Alexis
 * @brief This class implement the base entity.
 */

#include "Entity.hh"
#include "WorldPools.hh"

namespace ECS {
    namespace Entity {
    
	Entity::Entity()
	{}

	Entity::~Entity()
	{}
	
	Component::AComponent	*Entity::getComponent(Component::ComponentType type)
	{
	    Component::AComponent *component;
	    std::map<Component::ComponentType, Component::AComponent *>::iterator it;

	    it = _components.find(type);
	    if (it == _components.end())
		component = nullptr;
	    else
		component = (*it).second;

	    return component;
	}

	void	Entity::extractComponents(std::vector<Component::AComponent *> &vector)
	{
	    for (auto &kv : _components) {
		vector.push_back(kv.second);
	    }
	    _components.clear();
	}

    }
}
