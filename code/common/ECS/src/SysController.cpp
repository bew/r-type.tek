/**
 * @file SysController.cpp
 * @author Nekhot
 * @brief Impelmentation of system procesing controller data.
 */
#include <iostream>
#include "SysController.hh"

namespace ECS {
  namespace System {

    ECS::Entity::Entity *SysController::fire(WorldData &world, ECS::Entity::Entity *entity) {
      Component::CompBlueprint *blueprintc = dynamic_cast<Component::CompBlueprint*>(world._systemEntity.getComponent(ECS::Component::BLUEPRINT));
      Component::CompProjectile *projectilec = dynamic_cast<Component::CompProjectile*>(entity->getComponent(ECS::Component::PROJECTILE));
      Component::CompMovement *ownerMovementc = dynamic_cast<Component::CompMovement*>(entity->getComponent(ECS::Component::MOVEMENT));
      Component::CompTick *tickc = dynamic_cast<Component::CompTick*>(world._systemEntity.getComponent(ECS::Component::TICK));
      ECS::Entity::Entity *projectile = nullptr;

      if (blueprintc && projectilec && tickc && ownerMovementc && tickc->tick - projectilec->lastFireTick > projectilec->fireRate) {
	try {
	  projectile = new ECS::Entity::Entity(blueprintc->getNextID());
	  for (ECS::Component::AComponent *component : blueprintc->blueprints.at(projectilec->name))
	    projectile->addComponent(component->clone());
	  if (ownerMovementc) {
	    Component::CompMovement *projectileMovementc = dynamic_cast<Component::CompMovement*>(projectile->getComponent(ECS::Component::MOVEMENT));
	    projectileMovementc->_coo._x += ownerMovementc->_coo._x;
	    projectileMovementc->_coo._y += ownerMovementc->_coo._y;
	  }
	  projectilec->lastFireTick = tickc->tick;
	  logs::logger[logs::INFO] << "Blueprint '" << projectilec->name << "' instanciated" << std::endl;
	}
	catch (const std::out_of_range &e) {
	  logs::logger[logs::ERRORS] << "Blueprint '" << projectilec->name << "' does not exist" << std::endl;
	}
	catch (const ECS::Component::ComponentFlagException &e) {
	  logs::logger[logs::ERRORS] << "Cannot clone '" << projectilec->name << "' : '" << e.what() << "'" << std::endl;
	}
      }
      return projectile;
    }

    void SysController::update(WorldData &world) {
      Component::CompController *controllerc;
      Component::CompMovement *movementc;
      std::vector<ECS::Entity::Entity *> generatedEntities;

      for (ECS::Entity::Entity *entity : world._gameEntities) {
	controllerc = dynamic_cast<Component::CompController*>(entity->getComponent(ECS::Component::CONTROLLER));
	movementc = dynamic_cast<Component::CompMovement*>(entity->getComponent(ECS::Component::MOVEMENT));

	if (controllerc && movementc) {
	  movementc->_dir = {0, 0};
	  movementc->_speed = 0;
	  if (controllerc->up) 
	    movementc->_dir._y -= 1;
	  if (controllerc->down) 
	    movementc->_dir._y += 1;
	  if (controllerc->left) 
	    movementc->_dir._x -= 1;
	  if (controllerc->right) 
	    movementc->_dir._x += 1;
	  if (controllerc->up || controllerc->down || controllerc->left || controllerc->right)
	    movementc->_speed = 10;
	  if (controllerc->fire) {
	    ECS::Entity::Entity *projectile = this->fire(world, entity);
	    if (projectile)
	      generatedEntities.push_back(projectile);
	  }
	}
      }
      world._gameEntities.insert(world._gameEntities.end(), generatedEntities.begin(), generatedEntities.end());	    	  
    }
  }
}
