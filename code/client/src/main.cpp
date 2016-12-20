/**
 * @file main.cpp
 * @author Nekhot.
 * @brief Dummy main for client. Create an ecs loop with a windowComponent
 */

#include <iostream>
#include "SysWindow.hh"
#include "CompWindow.hh"
#include "ECS/CompEvent.hh"
#include "ECS/SysEvent.hh"
#include "ECS/CompTick.hh"
#include "ECS/SysTick.hh"
#include "Graphic/AssetStore.hpp"

int main(void) {

  ECS::World world;
  
  world.addSystem(new ECS::System::SysTick());
  world.addSystem(new ECS::System::SysWindow());
  world.addSystem(new ECS::System::SysEvent());
  
  world.addSystemEntityComponent(new ECS::Component::CompTick());
  world.addSystemEntityComponent(new ECS::Component::CompWindow());
  world.addSystemEntityComponent(new ECS::Component::CompEvent());

  int i = 0;
  while(true) {
    world.update();
    std::cout << "Tick : " << i++ << std::endl;
  }
  return 0;
};
