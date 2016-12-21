/**
 * @file SysController.cpp
 * @author Nekhot
 * @brief Impelmentation of system procesing controller data.
 */

#include "SysController.hh"

namespace ECS {
  namespace System {

    void SysController::update(WorldData &world) {
      Component::CompMovement *movementc;
      
      for (ECS::Entity::Entity *entity : world._gameEntities) {
	movementc = dynamic_cast<Component::CompMovement*>(entity->getComponent(ECS::Component::MOVEMENT));
	if (movementc) {
	  movementc->_dir._x = 0;
	  movementc->_dir._y = 0;

	  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	    movementc->_dir._x -= 1;
	  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            movementc->_dir._x += 1;
	  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            movementc->_dir._y += 1;
	  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            movementc->_dir._y -= 1;
	  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
	      || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
	      || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
	      || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	    movementc->_speed = 1;// ?
	}
      }
    }
  }
}

