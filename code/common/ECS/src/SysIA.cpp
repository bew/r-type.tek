/**
 * @file SysIA.cpp
 * @author Nekhot
 * @brief Impelmentation of system applying ia.
 */
#include "SysIA.hh"

namespace ECS {
  namespace System {
    void SysIA::update(WorldData &world) {
      Component::CompTick *tickc = dynamic_cast<Component::CompTick *>(world._systemEntity.getComponent(Component::TICK));

      if (tickc)
        for (Entity::Entity *entity : world._gameEntities) {
          Component::CompIA *iac = dynamic_cast<Component::CompIA *>(entity->getComponent(Component::IA));
	  Component::CompMovement *movementc = dynamic_cast<Component::CompMovement *>(entity->getComponent(Component::MOVEMENT));

	  if (movementc && iac && iac->name == "sin") {
	    if (iac->born == -1)
	      iac->born = tickc->tick;
	    movementc->_coo._x -= 1280 / 60 / 10;
	    movementc->_coo._y = sin((tickc->tick - iac->born) / (3.14159265 * 16.0)) * 280 + 720 / 2;
          }
        }
    }
  }
}
