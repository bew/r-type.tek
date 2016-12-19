/**
 * @file main.cpp
 * @author Nekhot.
 * @brief Dummy main for client. Create an ecs loop with a windowComponent
 */

#include "SysWindow.hh"
#include "CompWindow.hh"
#include "Graphic/AssetStore.hpp"

int main(void) {

  ECS::World world;
  graphic::GroupedAssetStore test("asset", "test");
  world.addSystem(new ECS::System::SysWindow());
  world.addSystemEntityComponent(new ECS::Component::CompWindow());
  while(true) {
    world.update();
  }
  return 0;
};
