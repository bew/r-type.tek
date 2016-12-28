/**
 * @file CompDeath.cpp
 * @author Nekhot.
 * @brief Implementation of Component to signal entity as dead.
 */

#include "CompDeath.hh"

namespace ECS {
  namespace Component { 
    const std::string &CompDeath::getType() const {
      return Component::DEATH;
    }
  }
}
