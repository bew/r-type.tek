
/*
** Started by Alexis Mongin 2016-11-30
*/

/*

This abstract class is destinated to manipulate the components.

*/

#pragma once

#include <map>

class AComponent
{
public:
    AComponent() = delete;
    virtual ~AComponent();

    AComponent(const AComponent &) = delete;
    AComponent &operator=(const AComponent &) = delete;

    enum ComponentType : unsigned char {
	NONE = 0,
        TYPE,
	SPRITE,
	LIFE,
	MOVEMENT,
	SHOOT,
	NETWORK,
	GRAPHX,    
    };
    
    virtual ComponentType	getType() const = 0;

private:
    std::map<ComponentType, AComponent *>	_component;
    const ComponentType	_type;
};
