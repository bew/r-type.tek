#pragma once
#include <vector>
#include <string>
#include <stdexcept>

typedef std::runtime_error ECSException;

class Component {
  public:
  Component(const std::string &pname) : name(pname) {};
  std::string name;
};

class Entity {
public:
  std::vector<Component*> _components;
  Component *getComponent(const std::string &search) {
    for (auto i : _components) {
      if (i->name == search)
	return i; 
    }
    throw ECSException(std::string("Could not find component '") + search + "'");
  };
};

class System {
public:
  virtual void process(Entity &) = 0;
};

class ECS {
public:
  std::vector<System*> _systems;
  void process(std::vector<Entity> &entities) {
    for (auto entity: entities) {
      for (auto system : _systems) {
	system->process(entity);
      }
    }
  };
};
