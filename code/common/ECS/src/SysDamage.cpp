/**
 * @file SysDamage.cpp
 * @author Nekhot
 * @brief Impelmentation of system applying damage to collided entity.
 */
#include "SysDamage.hh"

namespace ECS {
  namespace System {
    void SysDamage::update(WorldData &world) {
      Component::CompCollision *collisionc = dynamic_cast<Component::CompCollision *>(world._systemEntity.getComponent(Component::COLLISION));
      Component::CompTick *tickc = dynamic_cast<Component::CompTick *>(world._systemEntity.getComponent(Component::TICK));

      if (collisionc && tickc)
	for (Component::CompCollision::Collision pair : collisionc->_collisions) {
	  Component::CompType *typeA = dynamic_cast<Component::CompType *>(pair.entity_a->getComponent(Component::TYPE));
	  Component::CompLife *lifeA = dynamic_cast<Component::CompLife *>(pair.entity_a->getComponent(Component::LIFE));
          Component::CompDamage *damageA = dynamic_cast<Component::CompDamage *>(pair.entity_a->getComponent(Component::DAMAGE));
	  Component::CompType *typeB = dynamic_cast<Component::CompType *>(pair.entity_b->getComponent(Component::TYPE));
	  Component::CompLife *lifeB = dynamic_cast<Component::CompLife *>(pair.entity_b->getComponent(Component::LIFE));
          Component::CompDamage *damageB = dynamic_cast<Component::CompDamage *>(pair.entity_b->getComponent(Component::DAMAGE));

	  if (typeA && typeB && (typeA->_type & ECS::Component::CompType::FILTER_TEAM) != (typeB->_type & ECS::Component::CompType::FILTER_TEAM)) {
	    if (lifeA && damageB) {
	      lifeA->setCurrentLife(lifeA->getCurrentLife() - damageB->damage, tickc->tick);
	      if ((typeB->_type & ECS::Component::CompType::FILTER_TYPE) == ECS::Component::CompType::PROJECTILE) {
		pair.entity_b->addComponent(new ECS::Component::CompDeath());
	      }
	    }
	    if (lifeB && damageA) {
	      lifeB->setCurrentLife(lifeB->getCurrentLife() - damageA->damage, tickc->tick);		    
	      if ((typeA->_type & ECS::Component::CompType::FILTER_TYPE) == ECS::Component::CompType::PROJECTILE) {
		pair.entity_a->addComponent(new ECS::Component::CompDeath());
	      }
	    }
	  }
	}
    }
  }
}
