/**
 * @file SysAssets.hh
 * @author Nekhot.
 * @brief Header of System for loading standard asset.
 */

#pragma once

#include "ECS/World.hh"
#include "ECS/Entity.hh"
#include "ECS/ISystem.hh"
#include "Graphic/SpriteAsset.hh"
#include "CompAsset.hh"
#include "CompWindow.hh"
#include "CompSprite.hh"
#include "ECS/CompMovement.hh"
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

