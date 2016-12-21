/**
 * @file SysOptions.hh
 * @author Nekhot
 * @brief Header of System for emitting event on configuration change.
 */

#pragma once

#include "ECS/World.hh"
#include "ECS/Entity.hh"
#include "ECS/ISystem.hh"
#include "ECS/CompEvent.hh"
#include "CompOptions.hh"

namespace ECS {
  namespace System {

    /**
     * System for Options
     */
    class SysOptions : public ISystem {
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
