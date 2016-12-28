/**
 * @file SysKeyboard.cpp
 * @author Nekhot
 * @brief Impelmentation of system procesing keyboard input into raw data.
 */
#include <iostream>
#include "SysKeyboard.hh"

namespace ECS {
  namespace System {

    void SysKeyboard::update(WorldData &world) {
      Component::CompController *controllerc;

      for (ECS::Entity::Entity *entity : world._gameEntities) {
	controllerc = dynamic_cast<Component::CompController*>(entity->getComponent(ECS::Component::CONTROLLER));
	if (controllerc) {
	  controllerc->left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	  controllerc->right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
	  controllerc->up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	  controllerc->down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	  controllerc->fire = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
	}
      }
    }
  }
}
