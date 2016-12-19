#pragma once

/**
 * @file SysWindow.hh
 * @author Nekhot.
 * @brief System for processing windows.
 */

#include "ECS/World.hh"
#include "ECS/Entity.hh"
#include "ECS/ISystem.hh"
#include "CompWindow.hh"

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
