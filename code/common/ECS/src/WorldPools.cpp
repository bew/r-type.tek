
/**
 * @file WorldPools.cpp
 * @brief Implementation of an encapsulation of all the generic object pools.
 * @author Alexis Mongin
 *
 */

#include "AComponent.hh"
#include "WorldPools.hh"

#include <vector>

namespace ECS {

    namespace Pools {

	WorldPools::WorldPools()
	    : _entityPool(ObjectPool<Entity::Entity,
			  CommonFactory<Entity::Entity>>(NB_BASE_ELEM)),
	      _componentTestPool(ObjectPool<Component::ComponentTest,
				 CommonFactory<Component::ComponentTest>>(NB_BASE_ELEM))
	{}

	WorldPools::~WorldPools()
	{}

	void	WorldPools::operator>>(Entity::Entity *&obj)
	{
	    _entityPool >> obj;
	}

	void	WorldPools::operator<<(Entity::Entity *&obj)
	{
	    std::vector<Component::AComponent *> trash;

	    obj->extractComponents(trash);
	    for (auto &e : trash)
		*this << e;
	    _entityPool << obj;
	}

	void	WorldPools::operator>>(Component::ComponentTest *&obj)
	{
	    _componentTestPool >> obj;
	}

	void	WorldPools::operator<<(Component::ComponentTest *&obj)
	{
	    _componentTestPool << obj;
	}
	
	void	WorldPools::operator<<(Component::AComponent *&obj)
	{
	    Component::ComponentType	type;

	    type = obj->getType();
	    switch(type) {
	    case Component::ComponentType::TEST :
		Component::ComponentTest *buf;
	        buf = static_cast<Component::ComponentTest *>(obj);
		_componentTestPool << buf;
		break;
	    }
	}

    }
}
