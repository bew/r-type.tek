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
#include "ECS/CompAsset.hh"
#include "CompWindow.hh"
#include "ECS/CompSprite.hh"
#include "ECS/CompMovement.hh"
#include "Logs/Logger.hh"
#include "ECS/AssetLogLevel.hh"
#include "ECS/CompTick.hh"
#include "Graphic/SpriteAsset.hh"
#include "Graphic/AnimatedSpriteAsset.hh"
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

    protected:
      /**
       * Draw a single entity.
       *
       * @param entity The entity to draw
       * @param world All the data about the world
       */
      void update(Entity::Entity *entity, ECS::WorldData &world);
    };
  }
}

