/**
 * @file CompDeath.cpp
 * @author Nekhot.
 * @brief Implementation of Component to signal entity as dead.
 */

#include "CompDeath.hh"

namespace ECS {
  namespace Component {
    CompDeath::CompDeath(int delay) :
      _delay(delay)
    {}
    
    const std::string &CompDeath::getType() const {
      return Component::DEATH;
    }

    AComponent *CompDeath::clone(void) const {
      return new CompDeath(_delay);
    }

  }
}
