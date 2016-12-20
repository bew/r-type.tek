/**
 * @file SysTick.hh
 * @author Nekhot.
 * @brief System for processing tick.
 */

#pragma once

#include <thread>

#include "World.hh"
#include "Entity.hh"
#include "ISystem.hh"
#include "CompTick.hh"

namespace ECS {
  namespace System {

    /**
     * System for window
     */
    class SysTick : public ISystem {
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
