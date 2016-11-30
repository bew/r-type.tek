
// written by Alexis Mongin. Started 2016-09-10

/*

This is an abstraction for the object pool. Putting the ObjectPool template
class behind a single compilation dependency will reduce the compile time
and simplify the access behind all the pools.

Basically, create a pool of the object you need, and the related factory
(check ObjectPool.hpp) in ObPoolFactories.hh, then overload the << >>
operators of the world factory and the type of your object.

*/

#pragma once

#include "ObPoolFactories.hh"
#include "Entity.hh"
#include "ObjectPool.hpp"

class WorldFactories
{
public:
    WorldFactories();
    ~WorldFactories();

    WorldFactories(const WorldFactories &) = delete;
    WorldFactories &operator=(const WorldFactories &) = delete;

    void	operator<<(Entity *obj);
    void	operator>>(Entity *&obj);
    
private:
    ObjectPool<Entity, EntityFactory>	_entityPool;
};
