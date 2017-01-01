/**
 * @file SysMenu.hh
 * @author Heuse.
 * @brief Header of System for Menu.
 */

#pragma once

#include <iostream>

#include "ECS/World.hh"
#include "ECS/Entity.hh"
#include "ECS/ISystem.hh"
#include "Graphic/SpriteAsset.hh"
#include "ECS/CompSprite.hh"
#include "ECS/CompMovement.hh"
#include "Logs/Logger.hh"
#include "ECS/AssetLogLevel.hh"
#include "ECS/CompTick.hh"
#include "Graphic/SpriteAsset.hh"
#include "Graphic/AnimatedSpriteAsset.hh"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics.hpp"
#include "Protocol/Client.hh"
#include "ECS/CompScore.hh"
#include "ECS/CompLife.hh"
#include "Network/SocketException.hh"
#include "LibraryLoader/CompGenerator.hh"
#include "ECS/CompBlueprint.hh"
#include "ECS/CompSprite.hh"
#include "ECS/CompMusic.hh"

#include "SysWindow.hh"
#include "CompStateMachine.hh"
#include "CompNetworkClient.hh"
#include "CompAsset.hh"
#include "CompWindow.hh"
#include "CompLogin.hh"
#include "CompOptions.hh"

namespace ECS {
  namespace System {

    /**
     * System for Menu
     */
    class SysMenu : public ISystem {
    public:

      SysMenu();
      /**
       * Update method
       *
       * @param world All the data about the world
       */
      virtual void update(ECS::WorldData &world);


      /**
       * Draw the main menu
       *
       * @param world All the data about the world
       */      
      void menuSignup(ECS::WorldData &world);

      /**
       * Draw the room choose menu. Multi only
       *
       * @param world All the data about the world
       */            
      void menuRoomChoose(ECS::WorldData &world);

      /**
       * Draw the menu for waiting game beginning
       *
       * @param world All the data about the world
       */
      void menuGameLaunch(ECS::WorldData &world);

      /**
       * Draw the game gui
       *
       * @param world All the data about the world
       */
      void running(ECS::WorldData &world);

      
      /**
       * Draw the game end menu
       *
       * @param world All the data about the world
       */
      void menuEnd(ECS::WorldData &world);

      /**
       * Fill login components with generators, and determine room ownership
       *
       * @param world All the data about the world
       */
      void getGenerators(ECS::WorldData &world);

      /**
       * Add player entity with id 1, and emulate server by loading a generator and a blueprints component
       *
       * @param world All the data about the world
       */      
      void beginSolo(ECS::WorldData &world);
      
      typedef void(SysMenu::*Menu)(ECS::WorldData &world);

    private:
      unsigned index;
      bool up;
      bool down;
      std::string text_input;
      bool validate;

      std::map<std::string, Menu> _reactions;
    };
  }
}
