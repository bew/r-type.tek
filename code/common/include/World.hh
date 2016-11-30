
/*
** Started by Alexis Mongin 2016-11-30
*/

/*

This class implement the whole world of the R-Type !

*/

#pragma once

#include "ISystem.hh"
#include "Entity.hh"
#include "WorldData.hh"

#include <vector>

class World
{
public:
    World();
    ~World();

    World(const World &) = delete;
    World &operator=(const World &) = delete;

    struct WorldData
    {
	std::vector<std::string>	_packetsRead;
	std::vector<std::string>	_packetsToWrite;
	std::vector<Entity>		_gameEntities;
	Entity				_systemEntity;
    };

    void	update();

private:
    std::vector<ISystem *>	_systems;
    WorldData			_world;
    WorldFactories		_factories;
};
