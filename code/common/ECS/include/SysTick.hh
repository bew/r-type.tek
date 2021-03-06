/**
 * @file SysTick.hh
 * @author Nekhot.
 * @brief System for processing tick. Increment tick and block the thread to prevent ecs to run too fast.
 */

#pragma once

#include <thread>

#include "World.hh"
#include "Entity.hh"
#include "ISystem.hh"
#include "CompTick.hh"
#include "Logs/Logger.hh"

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
