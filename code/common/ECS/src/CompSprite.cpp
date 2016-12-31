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
      AComponent(CLONABLE_MASK | SERVER_SERIALIZABLE_MASK),
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
    
    bson::Document CompSprite::serialize() const {
      bson::Document doc;
      doc << "name" << name;
      doc << "center_x" << center._x;
      doc << "center_y" << center._y;
      doc << "animation" << animation;
      doc << "scale_x" << scale._x;
      doc << "scale_y" << scale._y;
      return doc;
    };

    void  CompSprite::deserialize(const bson::Document& document) {
      double sx, sy;
      document["name"] >> name;
      document["center_x"] >> center._x;
      document["center_y"] >> center._y;
      document["animation"] >> animation;
      document["scale_x"] >> sx; scale._x = sx;
      document["scale_y"] >> sy; scale._y = sy;
    }
  }
}
