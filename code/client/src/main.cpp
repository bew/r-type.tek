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
  ECS::Component::Music *music = new ECS::Component::CompMusic();
  ECS::Component::Music *event = new ECS::Component::CompEvent();

  //THATS DANGEROUS, JUST FOR TESTING (ref or ptr catpure are not safe, (with the exception of the even component that is garantee to be existing at event execution time)
  event.addHook("initialized", [=music](IEvent *event) {
      music->playing = true;
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
  world.addSystemEntityComponent(new ECS::Component::CompAsset());

  int i = 0;
  while(true) {
    world.update();
    std::cout << "Tick : " << i++ << std::endl;
  }
  return 0;
};
