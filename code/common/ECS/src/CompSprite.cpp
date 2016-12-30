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
    
    CompSprite::CompSprite(const std::string &pname, coordinates<int> coor, const std::string &animationName, const coordinates<float> &pscale) :
      AComponent(CLONABLE_MASK),
      name(pname),
      center(coor),
      animation(animationName),
      animationTick(-1),
      scale(pscale)
    {};

    AComponent *CompSprite::clone(void) const {
      return new CompSprite(name, center, animation, scale);
    }

    const std::string &CompSprite::getType() const {
      return Component::SPRITE;
    }
  }
}
