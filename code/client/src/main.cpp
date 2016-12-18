#include "WindowSystem.hh"

int main(void) {

  Entity world;
  ECS loop;
  std::vector<Entity> container;
  
  wolrd._components.push_back(new WindowComponent());
  container.push_back(world);
  while(true) {
    loop->process(container);
  }
  return 0;
};
