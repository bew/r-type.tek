
/*
** Started by Alexis Mongin 2016-11-30
*/

/*
** Put the E in... E C S 
*/

#pragma once

#include "AComponent.hh"

#include <map>

class Entity
{
public:
    Entity();
    ~Entity();

    Entity(const Entity &) = delete;
    Entity &operator=(const Entity &) = delete;

    AComponent	*getComponent(AComponent::ComponentType) const;
    void	addComponent(AComponent::ComponentType, AComponent *);
    
private:
    std::map<AComponent::ComponentType, AComponent *>	_component;
};
