/**
 * @file CompDamage.cpp
 * @author Nekhot.
 * @brief Implementation of Component to store an amount of damage.
 */

#include "CompDamage.hh"

namespace ECS {
  namespace Component {
    CompDamage::CompDamage(int amount) :
      AComponent(CLONABLE_MASK),
      damage(amount) {
    }

    const std::string &CompDamage::getType() const {
      return Component::DAMAGE;
    }

    AComponent *CompDamage::clone(void) const {
      return new CompDamage(damage);
    }
  }
}
