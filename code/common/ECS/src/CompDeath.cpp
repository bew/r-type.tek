/**
 * @file CompDeath.cpp
 * @author Nekhot.
 * @brief Implementation of Component to signal entity as dead.
 */

#include "CompDeath.hh"

namespace ECS {
  namespace Component {
    CompDeath::CompDeath(int delay) :
      AComponent(CLONABLE_MASK),
      _delay(delay)
    {}
    
    const std::string &CompDeath::getType() const {
      return Component::DEATH;
    }

    AComponent *CompDeath::clone(void) const {
      return new CompDeath(_delay);
    }

      bson::Document  CompDeath::serialize() const {
          bson::Document doc;
          doc << u8"delay" << _delay;
          return doc;
      };

      void  CompDeath::deserialize(const bson::Document& document) {
          document[u8"delay"] >> _delay;
      }

  }
}
