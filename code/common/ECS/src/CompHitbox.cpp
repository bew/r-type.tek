
/**
 * @file CompHitbox.cpp
 * @author Alexis.
 * @brief This component implement the hitboxes of game entities.
 *
 */

#include "CompHitbox.hh"

namespace ECS {
    namespace Component {

	CompHitbox::CompHitbox(unsigned mid_width, unsigned mid_height)
	    : AComponent(HITBOX), _midWidth(mid_width), _midHeight(mid_height)
	{
	}

	CompHitbox::~CompHitbox()
	{    
	}
    }
}
