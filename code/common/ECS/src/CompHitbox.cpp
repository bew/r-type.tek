/**
 * @file CompHitbox.cpp
 * @author Alexis.
 * @brief This component implement the hitboxes of game entities.
 *
 */

#include <CompHitbox.hh>
#include "CompHitbox.hh"

namespace ECS
{
  namespace Component
  {

    CompHitbox::CompHitbox(void) {};
    
    CompHitbox::CompHitbox(int mid_width, int mid_height)
      : AComponent(CLONABLE_MASK | SERVER_SERIALIZABLE_MASK), _midWidth(mid_width), _midHeight(mid_height)
    {
    }
    
    CompHitbox::~CompHitbox()
    {
    }
    
    AComponent *CompHitbox::clone(void) const {
      return new CompHitbox(_midWidth, _midHeight);
    }
    
    const std::string &CompHitbox::getType() const
    {
      return Component::HITBOX;
    }

      bson::Document  CompHitbox::serialize() const {
        bson::Document doc;
        doc << u8"midWidth" << _midWidth;
        doc << u8"midHeight" << _midHeight;
        return doc;
      };

      void  CompHitbox::deserialize(const bson::Document& document) {
        document[u8"midWidth"] >> _midWidth;
        document[u8"midHeight"] >> _midHeight;
      }
  }
}
