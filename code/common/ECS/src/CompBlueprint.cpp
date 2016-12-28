/**
 * @file CompBlueprint.cpp
 * @author Nekhot.
 * @brief Implementation of Component for blueprint.
 */

#include "CompBlueprint.hh"

namespace ECS {
  namespace Component {

    CompBlueprint::CompBlueprint(int offset) :
      nextID(offset)
    {};

    CompBlueprint::~CompBlueprint(void) {
      for (auto components : blueprints)
	for (Component::AComponent *component : components.second)
	  delete component;
    }

    int CompBlueprint::getNextID(void) {
      return nextID++;
    }
    
    const std::string &CompBlueprint::getType() const {
      return Component::BLUEPRINT;
    }
  }
}
