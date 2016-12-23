/**
 * @file SysWindow.hh
 * @author Nekhot.
 * @brief System for processing windows.
 */

#pragma once

#include "World.hh"
#include "Entity.hh"
#include "ISystem.hh"
#include "CompAsset.hh"
#include "CompMusic.hh"
#include "CompOptions.hh"
#include "Logger.hh"
#include "AssetLogLevel.hh"

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
