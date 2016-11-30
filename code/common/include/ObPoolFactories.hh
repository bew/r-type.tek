
// written by Alexis Mongin. Started 2016-09-10

/*

The factories needed for the object pool go there !

*/

#pragma once

#include "Entity.hh"

class EntityFactory()
{
public:
    EntityFactory();
    ~EntityFactory();

    Entity *operator()();

    void remove(Entity *);
}
