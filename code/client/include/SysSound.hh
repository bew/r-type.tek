/**
 * @file SysSound.hh
 * @author Nekhot.
 * @brief Header of System for playing sound.
 */

#pragma once

#include "ECS/World.hh"
#include "ECS/Entity.hh"
#include "ECS/ISystem.hh"
//USE THE CLIENT COMPSOUND, NOT THE SERVER ONE
#include "CompSound.hh"
#include "CompAsset.hh"
#include "SFML/Audio/Sound.hpp"
#include "ECS/AssetLogLevel.hh"
#include "CompOptions.hh"

namespace ECS {
  namespace System {

    /**
     * System for sounds
     */
    class SysSound : public ISystem {
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
