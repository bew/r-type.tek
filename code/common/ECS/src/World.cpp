
/**
 * @file World.cpp
 * @author Alexis
 * @brief This class implement the whole world of the R-Type !
 */

#include "World.hh"

namespace ECS
{

    WorldData::WorldData()
        : _gameEntities(), _systemEntity(0)
    {}

    WorldData::~WorldData()
    {
      for (Entity::Entity *entity : _gameEntities)
	delete entity;
    }

    World::World()
        : _systems(), _world()
    {
    }

    World::~World()
    {
      for (System::ISystem *system : _systems)
	delete system;
    }

    void World::addSystem(System::ISystem *system)
    {
        _systems.push_back(system);
    }

    void World::update()
    {
        for (auto &e : _systems)
            e->update(_world);
    }

    void World::addSystemEntityComponent(Component::AComponent *comp)
    {
        _world._systemEntity.addComponent(comp);
    }

    Entity::Entity *WorldData::getEntityById(int64_t id)
    {
      if (_systemEntity.getId() == id)
	return &_systemEntity;
      for (Entity::Entity *entity : _gameEntities) {
	if (entity->getId() == id)
	  return entity;
      }
      return nullptr;
    }

}
