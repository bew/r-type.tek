/**
 * @file SysKeybaord.hh
 * @author Nekhot.
 * @brief Header of System for computing user kyeboard input into serializable control.
 */

#pragma once

#include "ECS/World.hh"
#include "ECS/Entity.hh"
#include "ECS/ISystem.hh"
#include "SFML/Window/Keyboard.hpp"
#include "ECS/CompController.hh"

namespace ECS {
  namespace System {

    /**
     * System for controller
     */
    class SysKeyboard : public ISystem {
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
