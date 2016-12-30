/**
 * @file CompIA.cpp
 * @author Nekhot.
 * @brief Implementation of Component to store ia type.
 */

#include "CompIA.hh"

namespace ECS {
  namespace Component {

    CompIA::CompIA(const std::string &pname) :
      AComponent(CLONABLE_MASK),
      name(pname),
      born(-1) {
    }

    const std::string &CompIA::getType() const {
      return Component::IA;
    }

    AComponent *CompIA::clone(void) const {
      return new CompIA(name);
    }
  }
}