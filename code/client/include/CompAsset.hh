/**
 * @file CompAsset.hh
 * @author Nekhot
 * @brief Component for holding system entity standard asset.
 */

#pragma once

#include <string>
#include "Graphic/AssetStore.hpp"
#include "ECS/AComponent.hh"

namespace ECS {
  namespace Component {

    /**
     * The type of the asset component
     */
    static const std::string STANDARD_ASSET = "standard_asset";

    /**
     * Component for holding system entity standard asset.
     */
    class CompAsset : public AComponent {
    public:

      /**
       * Default constructor. Build a store at Asset/standard, with default locale
       */
      CompAsset(void);

      /**
       * The store containing standard assets.
       */
      graphic::GroupedAssetStore store;

      /**
       * If the store has already been loaded
       */
      bool loaded;

      /**
       * @return ECS::Component::STANDARD_ASSET
       */
      virtual const std::string &getType() const;
    };
  }
}
