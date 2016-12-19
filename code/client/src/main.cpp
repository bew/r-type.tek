#include <iostream>

#include "SysWindow.hh"
#include "CompWindow.hh"
#include "Graphic/AssetStore.hpp"

int main(void) {

  ECS::World world;
  graphic::GroupedAssetStore test("asset", "test");
  world.addSystem(new ECS::System::SysWindow());
  world.addSystemEntityComponent(new ECS::Component::CompWindow());
  while(true) {
    std::cout << "TICK" << std::endl;
    world.update();
  }
  return 0;
};
