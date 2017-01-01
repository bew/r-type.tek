/**
 * @file CompGenerator.cpp
 * @author Nekhot.
 * @brief Implementation of Component to hold generators.
 */

#include "CompGenerator.hh"

namespace ECS {
  namespace Component {
    CompGenerator::CompGenerator() :
      loaded(false)
    {}

    const std::string &CompGenerator::getType() const {
      return Component::GENERATOR;
    }
  }
}

