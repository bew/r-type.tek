/**
 * @file CompBlueprint.cpp
 * @author Nekhot.
 * @brief Implementation of Component for blueprint.
 */

#include "CompBlueprint.hh"

namespace ECS {
  namespace Component {

    const std::string &CompMusic::getType() const {
      return Component::BLUEPRINT;
    }
  }
}
