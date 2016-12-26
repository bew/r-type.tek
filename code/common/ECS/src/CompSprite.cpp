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
      name(pname),
      center(x, y)
    {};

    const std::string &CompSprite::getType() const {
      return Component::SPRITE;
    }
  }
}
