/**
 * @file SysDeath.hh
 * @author Nekhot.
 * @brief System for flushing entity that are no longer needed.
 */

#pragma once

#include <algorithm>
#include "World.hh"
#include "Entity.hh"
#include "ISystem.hh"
#include "CompDeath.hh"
#include "CompCollision.hh"
#include "CompSuccessor.hh"
#include "CompBlueprint.hh"
#include "CompMovement.hh"
#include "CompScore.hh"
#include "Logs/Logger.hh"

namespace ECS {
  namespace System {

    /**
     * System for window
     */
    class SysDeath : public ISystem {
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
