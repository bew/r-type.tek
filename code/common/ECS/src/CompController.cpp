/**
 * @file CompController.cpp
 * @author Nekhot.
 * @brief Implementation of Component for client control.
 */

#include "CompController.hh"

namespace ECS {
  namespace Component {
    const std::string &CompController::getType() const {
      return Component::CONTROLLER;
    };
    CompController::~CompController(void) {};
  }
}
