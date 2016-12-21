/**
 * @file SysController.hh
 * @author Nekhot.
 * @brief Header of System for computing user input into movement and other data.
 */

#pragma once

#include "ECS/World.hh"
#include "ECS/Entity.hh"
#include "ECS/ISystem.hh"
#include "ECS/CompMovement.hh"
#include "SFML/Window/Keyboard.hpp"

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
    };
  }
}
