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

    /**
     * type the asset component
     */
    static const std::string STANDARD_ASSET = "standard_asset";

    /**
     * Component for asset
     */
    class CompAsset : public AComponent {
    public:

      /**
       * Default constructor
       */
      CompAsset(void);

      /**
       * ptr to the underlying store for always loaded asset
       */
      graphic::GroupedAssetStore *store;

      /**
       * @return the type of asset
       */
      virtual const std::string &getType() const;

      /**
       * Default destructor
       */
      ~CompAsset(void);
    };
  }
}
