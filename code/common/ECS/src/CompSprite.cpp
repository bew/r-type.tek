/**
 * @file CompSprite.cpp
 * @author Nekhot
 * @brief Implementation of Component for sprites.
 */

#include "CompSprite.hh"

namespace ECS {
  namespace Component {

    const std::string CompSprite::NO_SPRITE = "";

    const std::string CompSprite::NO_ANIMATION  ="";
    
    CompSprite::CompSprite(const std::string &pname, coordinates<int> coor, const std::string &animationName) :
      AComponent(CLONABLE_MASK),
      name(pname),
      center(coor),
      animation(animationName)
    {};

    AComponent *CompSprite::clone(void) const {
      return new CompSprite(name, center, animation);
    }

    const std::string &CompSprite::getType() const {
      return Component::SPRITE;
    }
  }
}
