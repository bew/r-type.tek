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

      if (collisionc)
	for (Component::CompCollition::Collision pair : collisionc._collisions) {
	  Component::CompType *typeA = dynamic_cast<Component::CompType *>(pair.entity_a->getComponent(Component::TYPE));
	  Component::CompLife *lifeA = dynamic_cast<Component::CompLife *>(pair.entity_a->getComponent(Component::LIFE));
          Component::CompDamage *damageA = dynamic_cast<Component::CompDamagae *>(pair.entity_a->getComponent(Component::DAMAGE));
	  Component::CompType *typeB = dynamic_cast<Component::CompType *>(pair.entity_a->getComponent(Component::TYPE));
	  Component::CompLife *lifeB = dynamic_cast<Component::CompLife *>(pair.entity_b->getComponent(Component::LIFE));
          Component::CompDamage *damageB = dynamic_cast<Component::CompDamage *>(pair.entity_b->getComponent(Component::DAMAGE));
	  //faire des papouilles
	}
    }
  }
}
