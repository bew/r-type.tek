
/**
 * @file Entity.hh
 * @author Alexis
 * @brief This class implement the base entity.
 */

#include "Entity.hh"

namespace ECS {
    namespace Entity {
    
	Entity::Entity()
	{}

	Entity::~Entity()
	{}
	
	Component::AComponent	*Entity::getComponent(const std::string &type)
	{
	    Component::AComponent *component;
	    std::map<const std::string, Component::AComponent *>::iterator it;

	    it = _components.find(type);
	    if (it == _components.end())
		component = nullptr;
	    else
		component = (*it).second;

	    return component;
	}
    }
}
