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
#include "ECS/CompEvent.hh"
#include "ECS/SysEvent.hh"
#include "ECS/CompTick.hh"
#include "ECS/SysTick.hh"
#include "Graphic/AssetStore.hpp"

int main(void) {

  ECS::World world;
  ECS::Component::CompMusic *music = new ECS::Component::CompMusic();
  ECS::Component::CompEvent *event = new ECS::Component::CompEvent();
  ECS::Component::CompAsset *asset = new ECS::Component::CompAsset();

  music->setMusic("MilkyWay");

  //Plutot que d'utiliser une capture dangeureuse, il vaux mieux retrouver manuellement les components.
  event->addHook("initialized", [](ECS::Component::CompEvent::IEvent *event, ECS::WorldData &data) {
      ECS::Component::CompMusic *musicComponent = dynamic_cast<ECS::Component::CompMusic*>(data._systemEntity.getComponent(ECS::Component::MUSIC));
      ECS::Component::CompAsset *assetComponent = dynamic_cast<ECS::Component::CompAsset*>(data._systemEntity.getComponent(ECS::Component::STANDARD_ASSET));

      if (musicComponent && assetComponent && assetComponent->store) {
	try {
	  assetComponent->store->getMusic(musicComponent->getMusic()).getLowLevelMusic().play();
	}
	catch (const graphic::AssetException &e) {
	  std::cerr << e.what() << std::endl;
	}
      } //else error d'ordre d'initialisation.
      return false;
    });
  
  world.addSystem(new ECS::System::SysTick());
  world.addSystem(new ECS::System::SysWindow());
  world.addSystem(new ECS::System::SysAsset());
  world.addSystem(new ECS::System::SysMusic());
  world.addSystem(new ECS::System::SysEvent());
  
  world.addSystemEntityComponent(new ECS::Component::CompTick());
  world.addSystemEntityComponent(new ECS::Component::CompWindow());
  world.addSystemEntityComponent(event);
  world.addSystemEntityComponent(new ECS::Component::CompOptions());
  world.addSystemEntityComponent(music);
  world.addSystemEntityComponent(asset);

  int i = 0;
  while(true) {
    world.update();
    //std::cout << "Tick : " << i++ << std::endl;
  }
  return 0;
};
