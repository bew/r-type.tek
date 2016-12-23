/**
 * @file SysAssets.hh
 * @author Nekhot.
 * @brief Header of System for loading standard asset.
 */

#pragma once

#include "World.hh"
#include "Entity.hh"
#include "ISystem.hh"
#include "SpriteAsset.hh"
#include "CompAsset.hh"
#include "CompWindow.hh"
#include "CompSprite.hh"
#include "CompMovement.hh"
#include "Logger.hh"
#include "AssetLogLevel.hh"
#include "SFML/Graphics/Sprite.hpp"

namespace ECS {
  namespace System {

    /**
     * System for sprite
     */
    class SysSprite : public ISystem {
    public:

      /**
       * Update method
       *
       * @param world All the data about the world
       */
      virtual void update(ECS::WorldData &world);
    };
  }
}

