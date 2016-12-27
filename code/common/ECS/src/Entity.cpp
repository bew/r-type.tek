
/**
 * @file Entity.hh
 * @author Alexis
 * @brief This class implement the base entity.
 */

#include "Entity.hh"

namespace ECS {
    namespace Entity {
    
	Entity::Entity(int64_t  id)
            : _id(id), _components()
        {
        }

	Entity::~Entity()
	{
	  for (auto component : _components)
	    delete component.second;
	}
	
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

		int64_t        Entity::getId() const
        {
            return _id;
        }
        
        void  Entity::addComponent(ECS::Component::AComponent *comp)
        {
            _components[comp->getType()] = comp;
        }
        
    }
}
