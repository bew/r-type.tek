/**
 * @file SysEvent.hh
 * @author Nekhot.
 * @brief System for processing events.
 */

#pragma once

#include "World.hh"
#include "Entity.hh"
#include "ISystem.hh"
#include "CompEvent.hh"

namespace ECS {
  namespace System {

    /**
     * System for window
     */
    class SysEvent : public ISystem {
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
       * @param world All the data about the world
       */
      void update(ECS::Entity::Entity &entity, ECS::WorldData &world);

	  /**
	  * Helper method to update a single entity. Same as update but with fix for windows broken iterator
	  *
	  * @param entity The entity that will get updated
	  * @param world All the data about the world
	  */
	  void updateW(ECS::Entity::Entity &entity, ECS::WorldData &world);

    };
  }
}
