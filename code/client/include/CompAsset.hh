/**
 * @file CompAsset.hh
 * @author Nekhot.
 * @brief Component for entity that need there own windows.
 */

#pragma once

#include "Graphic/AssetStore.hpp"
#include "ECS/AComponent.hh"

namespace ECS {
  namespace Component {

    static const std::string STANDARD_ASSET = "standard_asset";

    /**
     * Component for music
     */
    class CompAsset : public AComponent {
    public:

      CompAsset(void);
      
      graphic::GroupedAssetStore *store;
      
      virtual const std::string &getType() const;

      ~CompAsset(void);
    };
  }
}
