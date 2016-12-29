/**
 * @file CompBlueprint.cpp
 * @author Nekhot.
 * @brief Implementation of Component for blueprint.
 */

#include "CompBlueprint.hh"

namespace ECS {
  namespace Component {

    CompBlueprint::CompBlueprint(int offset) :
      nextID(offset)
    {};

    CompBlueprint::~CompBlueprint(void) {
      for (auto components : blueprints)
	for (Component::AComponent *component : components.second)
	  delete component;
    }

    int CompBlueprint::getNextID(void) {
      return nextID++;
    }
    
    const std::string &CompBlueprint::getType() const {
      return Component::BLUEPRINT;
    }

    Entity::Entity *CompBlueprint::spawn(const std::string &name, Entity::Entity *owner) {
      Entity::Entity *projectile = new ECS::Entity::Entity(this->getNextID());
      try {
	for (ECS::Component::AComponent *component : this->blueprints.at(name))
	  projectile->addComponent(component->clone());
	if (owner) {
	  Component::CompMovement *ownerMovementc = dynamic_cast<Component::CompMovement*>(owner->getComponent(ECS::Component::MOVEMENT));
	  Component::CompMovement *projectileMovementc = dynamic_cast<Component::CompMovement*>(projectile->getComponent(ECS::Component::MOVEMENT));
	  Component::CompType *ownerTypec = dynamic_cast<Component::CompType*>(owner->getComponent(ECS::Component::TYPE));
	  Component::CompType *projectileTypec = dynamic_cast<Component::CompType*>(projectile->getComponent(ECS::Component::TYPE));

	  if (ownerMovementc && projectileMovementc) {
	    projectileMovementc->_coo._x += ownerMovementc->_coo._x;
	    projectileMovementc->_coo._y += ownerMovementc->_coo._y;
	  }
	  if (ownerTypec && projectileTypec)
	    projectileTypec->_type = (projectileTypec->_type & (~ECS::Component::CompType::FILTER_TEAM) | (ownerTypec->_type & ECS::Component::CompType::FILTER_TEAM));
	}
      }
      catch (const std::out_of_range &e) {
	delete projectile;
	throw ComponentFlagException(std::string("Blueprint '") + name + "' does not exist");
      }
      return projectile;
    }
  }
}
