/**
 * @file SysWindow.hh
 * @author Nekhot.
 * @brief System for processing windows.
 */

#pragma once

#include "World.hh"
#include "Entity.hh"
#include "ISystem.hh"
#include "CompEvent.hh"
#include "CompTick.hh"
#include "CompCollision.hh"
#include "CompWindow.hh"
#include "CompOptions.hh"

namespace ECS {
  namespace System {

    /**
     * System for window
     */
    class SysWindow : public ISystem {
    public:
      /**
       * Update method
       *
       * @param world All the data about the world
       */
      virtual void update(ECS::WorldData &world);
    protected:

      /**
       * Helper method to update a single entity
       *
       * @param entity The entity that will get updated
       */
      void update(ECS::Entity::Entity &entity);
    };
  }
}
