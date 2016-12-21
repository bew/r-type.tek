/**
 * @file CompWindow.cpp
 * @author Nekhot.
 * @brief Implementation of Component for entity that need there own windows.
 */

#include "CompAsset.hh"

namespace ECS {
  namespace Component {

    CompAsset::CompAsset(void) :
      store("asset", "standard")
    {};

    const std::string &CompAsset::getType() const {
      return Component::STANDARD_ASSET;
    }
  }
}
