/**
 * @file SysDeath.cpp
 * @author Nekhot.
 * @brief Impelmentation of system flusfing dead entity.
 */
#include "SysDeath.hh"

namespace ECS {
  namespace System {
    void SysDeath::update(WorldData &world) {
      remove_if(world._gameEntities.begin() , world._gameEntities.end(), [](Entity::Entity *entity) {
	  if (dynamic_cast<Component::CompDeath*>(entity->getComponent(Component::DEATH))) {
	    delete entity;
	    return true;
	  }
	  return false;
	});
    }
  }
}
