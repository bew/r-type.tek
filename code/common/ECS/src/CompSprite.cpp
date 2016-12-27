/**
 * @file CompSprite.cpp
 * @author Nekhot
 * @brief Implementation of Component for sprites.
 */

#include "CompSprite.hh"

namespace ECS {
  namespace Component {

    const std::string CompSprite::NO_SPRITE = "";
    
    CompSprite::CompSprite(const std::string &pname, int x, int y) :
      AComponent(CLONABLE_MASK),
      name(pname),
      center(x, y)
    {};

    AComponent *CompSprite::clone(void) const {
      return new CompSprite(name, center._x, center._y);
    }

    const std::string &CompSprite::getType() const {
      return Component::SPRITE;
    }
  }
}
