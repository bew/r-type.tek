/**
 * @file SysWindow.hh
 * @author Nekhot.
 * @brief System for processing windows.
 */

#pragma once

#include "ECS/World.hh"
#include "ECS/Entity.hh"
#include "ECS/ISystem.hh"
#include "ECS/CompAsset.hh"
#include "ECS/CompMusic.hh"
#include "CompOptions.hh"
#include "Logs/Logger.hh"
#include "ECS/AssetLogLevel.hh"

namespace ECS {
  namespace System {

    /**
     * System for window
     */
    class SysMusic : public ISystem {
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
