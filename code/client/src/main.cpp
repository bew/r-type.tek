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
#include "CompOptions.hh"
#include "SysMusic.hh"
#include "CompMusic.hh"
#include "SysSprite.hh"
#include "CompSprite.hh"
#include "SysController.hh"
#include "ECS/CompEvent.hh"
#include "ECS/SysEvent.hh"
#include "ECS/CompTick.hh"
#include "ECS/SysTick.hh"
#include "ECS/CompMovement.hh"
#include "Graphic/AssetStore.hpp"

int main(void) {

  ECS::World world;
  ECS::Component::CompMusic *music = new ECS::Component::CompMusic();
  ECS::Component::CompEvent *event = new ECS::Component::CompEvent();
  ECS::Component::CompAsset *asset = new ECS::Component::CompAsset();

  music->setMusic("MilkyWay");


  ///////////////////////////////////////
  
  event->addHook("initialization", [](ECS::Component::CompEvent::IEvent *, ECS::WorldData &data) {
      ECS::Component::CompAsset *assetComponent = dynamic_cast<ECS::Component::CompAsset*>(data._systemEntity.getComponent(ECS::Component::STANDARD_ASSET));
      if (assetComponent)
	assetComponent->store.loadAll();
      return false;
    });

  //add hook parser les options

  //add hook ouvrir la fenetre
  

  
  event->addHook("initialized", [](ECS::Component::CompEvent::IEvent *, ECS::WorldData &data) {
      ECS::Component::CompMusic *musicComponent = dynamic_cast<ECS::Component::CompMusic*>(data._systemEntity.getComponent(ECS::Component::MUSIC));
      ECS::Component::CompAsset *assetComponent = dynamic_cast<ECS::Component::CompAsset*>(data._systemEntity.getComponent(ECS::Component::STANDARD_ASSET));

      if (musicComponent && assetComponent) {
	try {
	  assetComponent->store.getMusic(musicComponent->getMusic()).getLowLevelMusic().play();
	}
	catch (const graphic::AssetException &e) {
	  std::cerr << e.what() << std::endl;
	}
      }
      return false;
    });

   event->addHook("endOfTick", [=](ECS::Component::CompEvent::IEvent *, ECS::WorldData &data) {
      ECS::Component::CompWindow *windowComponent = dynamic_cast<ECS::Component::CompWindow*>(data._systemEntity.getComponent(ECS::Component::WINDOW));
      if (windowComponent && windowComponent->window)//should be avoided
	windowComponent->window->display();
      return true;
    });



  //////////////////////////////////////////
  
  world.addSystem(new ECS::System::SysTick());
  world.addSystem(new ECS::System::SysWindow());
  world.addSystem(new ECS::System::SysController());
  world.addSystem(new ECS::System::SysAsset());
  world.addSystem(new ECS::System::SysMusic());
  world.addSystem(new ECS::System::SysSprite());
  world.addSystem(new ECS::System::SysEvent());
  
  
  world.addSystemEntityComponent(new ECS::Component::CompTick());
  world.addSystemEntityComponent(new ECS::Component::CompWindow());
  world.addSystemEntityComponent(event);
  world.addSystemEntityComponent(new ECS::Component::CompOptions());
  world.addSystemEntityComponent(music);
  world.addSystemEntityComponent(asset);

  event->addEvent("initialization", nullptr);


  ///////////////// Ajouter une entité de test

  ECS::Entity::Entity entity;
  ECS::Component::CompSprite sprite;
  ECS::Component::CompMovement movement;
  sprite.name = "burrito";
  movement._coo._x = 300;
  movement._coo._y = 300;
  entity.addComponent(&sprite);
  entity.addComponent(&movement);
  world._world._gameEntities.push_back(&entity);


  
  int i = 0;
  while(true) {
    world.update();
    event->addEvent("endOfTick", nullptr);
    //std::cout << "Tick : " << i++ << std::endl;
  }
  return 0;
};
