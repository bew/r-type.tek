/**
 * @file SysIA.hh
 * @author Nekhot.
 * @brief System for applying ia
 */

#pragma once

#include <algorithm>
#include <cmath>
#include <ctgmath>

#include "World.hh"
#include "Entity.hh"
#include "ISystem.hh"
#include "CompTick.hh"
#include "CompIA.hh"
#include "CompMovement.hh"
#include "Logs/Logger.hh"

namespace ECS {
  namespace System {

    /**
     * System for window
     */
    class SysIA : public ISystem {
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
