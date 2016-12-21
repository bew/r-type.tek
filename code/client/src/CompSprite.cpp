/**
 * @file CompSprite.cpp
 * @author Nekhot
 * @brief Implementation of Component for sprites.
 */

#include "CompSprite.hh"

namespace ECS {
  namespace Component {

    CompSprite::CompSprite(void) :
      name(""),
      center(0, 0)
    {};

    const std::string &CompSprite::getType() const {
      return Component::SPRITE;
    }
  }
}
