#include <iostream>
#include "WindowSystem.hh"

int main(void) {

  Entity world;
  ECS loop;
  std::vector<Entity> container;
  graphic::GroupedAssetStore test("asset", "test");

  loop._systems.push_back(new WindowSystem());
  world._components.push_back(new WindowComponent());
  container.push_back(world);
  while(true) {
    std::cout << "TICK" << std::endl;
    loop.process(container);
  }
  return 0;
};
