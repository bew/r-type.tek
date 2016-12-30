/**
 * @file CompSueccesor.cpp
 * @author Nekhot.
 * @brief Implementation of Component to hold a sucessor.
 */

#include "CompSuccessor.hh"

namespace ECS {
  namespace Component {
    CompSuccessor::CompSuccessor(const std::string &successor) :
      _successor(successor)
    {}

    const std::string &CompSuccessor::getType() const {
      return Component::SUCCESSOR;
    }

    AComponent *CompSuccessor::clone(void) const {
      return new CompSuccessor(_successor);
    }

  }
}
