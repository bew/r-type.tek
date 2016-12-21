/**
 * @file CompOptions.cpp
 * @author Nekhot.
 * @brief Implementation of Component for client options.
 */

#include "CompOptions.hh"

namespace ECS {
  namespace Component {

    CompOptions::CompOptions(void) :
      locale(graphic::AssetStore::DEFAULT_LOCALE)
    {};

    const std::string &CompOptions::getType() const {
      return Component::OPTIONS;
    }
  }  
}
