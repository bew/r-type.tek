
/**
 * @file Entity.hh
 * @author Alexis
 * @brief This class implement the base entity.
 */

#include "WorldPools.hh"
#include "APoolable.hh"
#include "Entity.hh"

namespace ECS {

    namespace Entity {
    
	Entity::Entity(Pools::WorldPools &pools)
	    : Pools::APoolable(pools)
	{
	}

	Entity::~Entity()
	{
	}
	
	Component::AComponent	*Entity::getComponent(Component::ComponentType type)
	{
	    return _component[type];
	}

	void	Entity::clean()
	{
	    // for (auto& kv : _component) {
	    //     _pools << kv.second;
	    // }
	    
	}

    }
}
