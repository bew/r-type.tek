/**
 * @file CompAsset.cpp
 * @author Nekhot
 * @brief Component for holding system entity standard asset.
 */

#include "CompAsset.hh"

namespace ECS {
  namespace Component {

    CompAsset::CompAsset(void) :
      store("asset", "standard"),
      loaded(false)
    {};

    const std::string &CompAsset::getType() const {
      return Component::STANDARD_ASSET;
    }
  }
}
