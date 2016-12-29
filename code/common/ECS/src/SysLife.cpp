/**
 * @file SysLife.cpp
 * @author Nekhot
 * @brief Impelmentation of system applying death to entity with life < 0.
 */
#include "SysLife.hh"

namespace ECS {
  namespace System {
    void SysLife::update(WorldData &world) {
      for (Entity::Entity *entity : world._gameEntities) {
	Component::CompLife *lifec = dynamic_cast<Component::CompLife *>(entity->getComponent(Component::LIFE));
	Component::CompDeath *deathc = dynamic_cast<Component::CompDeath *>(entity->getComponent(Component::DEATH));
	if (lifec && lifec->_currentLife <= 0 && !deathc) {
	  entity->addComponent(new Component::CompDeath());
	}
      }
    }
  }
}
