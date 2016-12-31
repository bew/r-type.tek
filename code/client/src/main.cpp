/**
 * @file main.cpp
 * @author Nekhot.
 * @brief Dummy main for client. Create an ecs loop with a windowComponent
 */

#include <iostream>
#include "SysWindow.hh"
#include "CompWindow.hh"
#include "SysAsset.hh"
#include "CompAsset.hh"
#include "SysMusic.hh"
#include "ECS/CompMusic.hh"
#include "SysSprite.hh"
#include "ECS/CompSprite.hh"
#include "ECS/CompCollision.hh"
#include "CompOptions.hh"
#include "SysKeyboard.hh"
#include "ECS/SysController.hh"
#include "SysOptions.hh"
#include "ECS/CompController.hh"
#include "ECS/CompEvent.hh"
#include "ECS/SysEvent.hh"
#include "ECS/CompTick.hh"
#include "ECS/SysTick.hh"
#include "ECS/CompMovement.hh"
#include "ECS/SysMovement.hh"
#include "ECS/SysCollision.hh"
#include "ECS/CompHitbox.hh"
#include "ECS/CompBlueprint.hh"
#include "ECS/CompProjectile.hh"
#include "Graphic/AssetStore.hpp"
#include "SysMenu.hh"

int main(int ac, char**av) {

    ECS::World world;
  logs::logger.registerLogLevel(&logs::assetLogLevel);
  logs::logger.registerBasicsLogLevel();
  
  ////////////////////////// ADD SYSTEMS TO WORLD
  
  // control time, Has absolut priority over any other system
  world.addSystem(new ECS::System::SysTick());
  // process options (read/write/events). Should be initilized before system that use options to avoid doing the same things multiple things
  world.addSystem(new ECS::System::SysOptions());
  // open, reopen, clear and display window. Should be initilized before running system that draw things
  world.addSystem(new ECS::System::SysWindow());
  // transform input to data(up, down, fire, left, right)
  world.addSystem(new ECS::System::SysKeyboard());
  // transform data to movement (speed, direction)
  world.addSystem(new ECS::System::SysController());
  // transform movement to  movement(position)
  world.addSystem(new ECS::System::SysMovement());
  // Initilize and update assets stores
  world.addSystem(new ECS::System::SysAsset());
  // not sure
  world.addSystem(new ECS::System::SysMusic());
  // put sprite onto window surface
  world.addSystem(new ECS::System::SysSprite());
  // process events that happen in the tick
  world.addSystem(new ECS::System::SysEvent());

  ///////////////////////// ADD UNIQUE COMPONENTS TO WORLD 

  ECS::Component::CompMusic *music = new ECS::Component::CompMusic();
  ECS::Component::CompBlueprint *blueprints = new ECS::Component::CompBlueprint();
  ECS::Component::CompTick *tick = new ECS::Component::CompTick();
  ECS::Component::CompEvent *event = new ECS::Component::CompEvent();
  
  music->setMusic("MilkyWay");
  blueprints->blueprints["dices"] = {
    new ECS::Component::CompMovement({0, 0}, 20, {1, 0}),
    new ECS::Component::CompSprite("dices"),
    new ECS::Component::CompHitbox(60, 60)
  };
  
  world.addSystemEntityComponent(blueprints);
  world.addSystemEntityComponent(tick);
  world.addSystemEntityComponent(new ECS::Component::CompWindow());
  world.addSystemEntityComponent(event);
  world.addSystemEntityComponent(new ECS::Component::CompOptions());
  world.addSystemEntityComponent(music);
  world.addSystemEntityComponent(new ECS::Component::CompAsset());
  
  ///////////////////////// ADD ENTITIES TO WORLD
  
  ECS::Entity::Entity *entity = new ECS::Entity::Entity(1);
  entity->addComponent(new ECS::Component::CompSprite("ship"));  
  entity->addComponent(new ECS::Component::CompMovement({300, 300}));
  entity->addComponent(new ECS::Component::CompHitbox(60, 60));
  entity->addComponent(new ECS::Component::CompController());
  entity->addComponent(new ECS::Component::CompProjectile("dices"));

  ECS::Entity::Entity *entityFixed = new ECS::Entity::Entity(2);
  entityFixed->addComponent(new ECS::Component::CompSprite("fly", {0, 0}, "default"));
  entityFixed->addComponent(new ECS::Component::CompMovement({600, 600}));
  entityFixed->addComponent(new ECS::Component::CompHitbox(60, 60));
  
  world._world._gameEntities.push_back(entity);
  world._world._gameEntities.push_back(entityFixed);

  //////////////////////// RUN THE WORLD
  
  while (!tick->kill) {
    world.update();
  }
  return 0;
}
