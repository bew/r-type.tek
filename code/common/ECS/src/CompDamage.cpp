/**
 * @file CompDamage.cpp
 * @author Nekhot.
 * @brief Implementation of Component to store an amount of damage.
 */

#include "CompDamage.hh"

namespace ECS {
  namespace Component {

    CompDamage::CompDamage(void) {};
    
    CompDamage::CompDamage(int amount) :
      AComponent(CLONABLE_MASK | SERVER_SERIALIZABLE_MASK),
      damage(amount) {
    }

      bson::Document  CompDamage::serialize() const {
          bson::Document doc;
          doc << u8"damage" << damage;
          return doc;
      };

      void  CompDamage::deserialize(const bson::Document& document) {
          document[u8"damage"] >> damage;
      }

    const std::string &CompDamage::getType() const {
      return Component::DAMAGE;
    }

    AComponent *CompDamage::clone(void) const {
      return new CompDamage(damage);
    }
  }
}
