/**
 * @file SysDamage.hh
 * @author Nekhot.
 * @brief System for applying damage to collided entity.
 */

#pragma once

#include <algorithm>
#include "World.hh"
#include "Entity.hh"
#include "ISystem.hh"
#include "CompDamage.hh"
#include "CompType.hh"
#include "CompCollision.hh"
#include "CompLife.hh"
#include "CompDeath.hh"
#include "CompTick.hh"
#include "CompSprite.hh"
#include "Logs/Logger.hh"

namespace ECS {
  namespace System {

    /**
     * System for window
     */
    class SysDamage : public ISystem {
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
