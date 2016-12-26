/**
 * @file main.cpp
 * @author Nekhot.
 * @brief Dummy main for client. Create an ecs loop with a windowComponent
 */

#include <iostream>
#include "SysWindow.hh"
#include "CompWindow.hh"

#include "SysAsset.hh"
#include "ECS/CompAsset.hh"
#include "SysMusic.hh"
#include "ECS/CompMusic.hh"
#include "SysSprite.hh"
#include "ECS/CompSprite.hh"

#include "CompOptions.hh"
#include "SysController.hh"
#include "SysOptions.hh"
#include "CompController.hh"

#include "ECS/CompEvent.hh"
#include "ECS/SysEvent.hh"
#include "ECS/CompTick.hh"
#include "ECS/SysTick.hh"
#include "ECS/CompMovement.hh"
#include "ECS/SysMovement.hh"
#include "ECS/CompHitbox.hh"
#include "Graphic/AssetStore.hpp"

int main(void) {

  logs::logger.registerLogLevel(&logs::assetLogLevel);
  
  ECS::World world;
  ECS::Component::CompMusic *music = new ECS::Component::CompMusic();
  ECS::Component::CompEvent *event = new ECS::Component::CompEvent();
  ECS::Component::CompAsset *asset = new ECS::Component::CompAsset();
  ECS::Component::CompTick *tick = new ECS::Component::CompTick();
  music->setMusic("MilkyWay");


  ///////////////////////////////////////
  
  event->addHook("initialization", [](ECS::Component::CompEvent::IEvent *, ECS::WorldData &data) {
      ECS::Component::CompAsset *assetComponent = dynamic_cast<ECS::Component::CompAsset*>(data._systemEntity.getComponent(ECS::Component::STANDARD_ASSET));
      if (assetComponent)
	assetComponent->store.loadAll();
      return false;
    });
  //add hook parser les options
  
  //////////////////////////////////////////
  
  world.addSystem(new ECS::System::SysTick());
  world.addSystem(new ECS::System::SysOptions());
  world.addSystem(new ECS::System::SysWindow());
  world.addSystem(new ECS::System::SysMovement());
  world.addSystem(new ECS::System::SysController());
  world.addSystem(new ECS::System::SysAsset());
  world.addSystem(new ECS::System::SysMusic());
  world.addSystem(new ECS::System::SysSprite());
  world.addSystem(new ECS::System::SysEvent());

  
  world.addSystemEntityComponent(tick);
  world.addSystemEntityComponent(new ECS::Component::CompWindow());
  world.addSystemEntityComponent(event);
  world.addSystemEntityComponent(new ECS::Component::CompOptions());
  world.addSystemEntityComponent(music);
  world.addSystemEntityComponent(asset);

  event->addEvent("initialization", nullptr);


  ///////////////// Ajouter une entité de test
  // necessite ECS::World::_world public 
  
  ECS::Entity::Entity *entity = new ECS::Entity::Entity(1);
  entity->addComponent(new ECS::Component::CompSprite("burrito"));  
  entity->addComponent(new ECS::Component::CompMovement({300, 300}));
  entity->addComponent(new ECS::Component::CompHitbox(60, 60));
  entity->addComponent(new ECS::Component::CompController());

  ECS::Entity::Entity *entityFixed = new ECS::Entity::Entity(2);
  entityFixed->addComponent(new ECS::Component::CompSprite("burrito"));
  entityFixed->addComponent(new ECS::Component::CompMovement({600, 600}));
  entityFixed->addComponent(new ECS::Component::CompHitbox(60, 60));
  
  world._world._gameEntities.push_back(entity);
  world._world._gameEntities.push_back(entityFixed);
  
  while (!tick->kill) {
    world.update();
  }
  return 0;
};
