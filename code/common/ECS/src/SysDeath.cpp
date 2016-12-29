/**
 * @file SysDeath.cpp
 * @author Nekhot.
 * @brief Impelmentation of system flushing dead entity.
 */
#include "SysDeath.hh"

namespace ECS {
  namespace System {
    void SysDeath::update(WorldData &world) {
      Component::CompBlueprint* blueprintc = dynamic_cast<Component::CompBlueprint*>(world._systemEntity.getComponent(Component::BLUEPRINT));
      std::vector<ECS::Entity::Entity *> generatedEntities;

      world._gameEntities.erase(remove_if(world._gameEntities.begin() , world._gameEntities.end(), [&](Entity::Entity *entity) {
	    Component::CompDeath* deathc = dynamic_cast<Component::CompDeath*>(entity->getComponent(Component::DEATH));
	    Component::CompSuccessor* successorc = dynamic_cast<Component::CompSuccessor*>(entity->getComponent(Component::SUCCESSOR));

	    if (deathc) {
	      if (deathc->_delay <= 0) {
		if (blueprintc && successorc) {
		  try {
		    Entity::Entity *successor = blueprintc->spawn(successorc->_successor, entity);
		    generatedEntities.push_back(successor);
		  }
		  catch (const ECS::Component::ComponentFlagException &e) {
		    logs::logger[logs::ERRORS] << "Cannot clone '" << successorc->_successor << "' : '" << e.what() << "'" << std::endl;
		  }
		}
		delete entity;
		return true;
	      }
	      else
		--deathc->_delay;
	  }
	  return false;
	  }), world._gameEntities.end());
      world._gameEntities.insert(world._gameEntities.end(), generatedEntities.begin(), generatedEntities.end());
    }
  }
}
