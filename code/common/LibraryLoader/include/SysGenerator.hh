/**
 * @file SysGenerator.hh
 * @author Nekhot.
 * @brief System for running generator.
 */

#pragma once

#include <algorithm>
#include "ECS/World.hh"
#include "ECS/Entity.hh"
#include "ECS/ISystem.hh"
#include "CompGenerator.hh"

namespace ECS {
  namespace System {

    /**
     * System for generator
     */
    class SysGenerator : public ISystem {
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
