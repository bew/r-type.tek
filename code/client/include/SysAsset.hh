/**
 * @file SysAssets.hh
 * @author Nekhot.
 * @brief Header of System for loading standard asset.
 */

#pragma once

#include "ECS/World.hh"
#include "ECS/Entity.hh"
#include "ECS/ISystem.hh"
#include "CompAsset.hh"
#include "CompOptions.hh" 

namespace ECS {
  namespace System {

    /**
     * System for window
     */
    class SysAsset : public ISystem {
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
