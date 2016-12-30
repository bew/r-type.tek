/**
 * @file SysLife.hh
 * @author Nekhot.
 * @brief System for applying death to entity with life < 0
 */

#pragma once

#include <algorithm>
#include "World.hh"
#include "Entity.hh"
#include "ISystem.hh"
#include "CompDeath.hh"
#include "CompLife.hh"
#include "Logs/Logger.hh"
#include "CompScore.hh"

namespace ECS {
  namespace System {

    /**
     * System for life
     */
    class SysLife : public ISystem {
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
