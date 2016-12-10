
/**
 * @file Entity.hh
 * @author Alexis
 * @brief This class implement the base entity.
 */

#include "Entity.hh"

namespace ECS {

    namespace Entity {
    
	Entity::Entity()
	{
	}

	Entity::~Entity()
	{
	}
	
	Component::AComponent	*Entity::getComponent(Component::ComponentType type)
	{
	    return _component[type];
	}

    }
}
