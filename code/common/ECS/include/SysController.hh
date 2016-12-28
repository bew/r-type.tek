/**
 * @file SysController.hh
 * @author Nekhot.
 * @brief Header of System for computing user input into movement and other data.
 */

#pragma once

#include <vector>
#include "World.hh"
#include "Entity.hh"
#include "ISystem.hh"
#include "CompMovement.hh"
#include "CompController.hh"
#include "CompBlueprint.hh"
#include "CompProjectile.hh"
#include "Logs/Logger.hh"
#include "CompTick.hh"

namespace ECS {
  namespace System {

    /**
     * System for controller
     */
    class SysController : public ISystem {
    public:

      /**
       * Update method
       *
       * @param world All the data about the world
       */
      virtual void update(ECS::WorldData &world);
    protected:
      /**
       * Fire a projectile for entity
       */
      ECS::Entity::Entity *fire(WorldData &world, ECS::Entity::Entity *entity);
    };
  }
}
