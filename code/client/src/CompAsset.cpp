/**
 * @file CompWindow.cpp
 * @author Nekhot.
 * @brief Implementation of Component for entity that need there own windows.
 */

#include "CompAsset.hh"

namespace ECS {
  namespace Component {

    CompAsset::CompAsset(void) :
      store(nullptr)
    {};

    const std::string &CompAsset::getType() const
    {
      return Component::STANDARD_ASSET;
    }

    CompAsset::~CompAsset(void) {
      delete store;
    }
  }
}
