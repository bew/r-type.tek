/**
 * @file SysGui.hh
 * @author Nekhot.
 * @brief Header of System for drawing gui.
 */

#pragma once

#include "ECS/World.hh"
#include "ECS/Entity.hh"
#include "ECS/ISystem.hh"
#include "CompAsset.hh"
#include "CompWindow.hh"
#include "Logs/Logger.hh"
#include "ECS/AssetLogLevel.hh"
#include "ECS/CompLife.hh"
#include "ECS/CompScore.hh"
#include "Graphic/SpriteAsset.hh"
#include "SFML/Graphics/Text.hpp"

namespace ECS {
  namespace System {

    /**
     * System for gui
     */
    class SysGui : public ISystem {
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

