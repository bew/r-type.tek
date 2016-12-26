/**
 * @file CompTick.cpp
 * @author Nekhot.
 * @brief Implementation for component tick.
 *
 */

#include "CompTick.hh"

namespace ECS
{
    namespace Component
    {
      
      const unsigned int CompTick::FREQUENCY = 60;

      CompTick::CompTick(void) :
	AComponent(),
	tick(0),
	tickDuration(1.0 / static_cast<float>(CompTick::FREQUENCY)),
	lag(0),
	kill(false)
      {}
      
      const std::string &CompTick::getType() const
      {
	return Component::TICK;
      }
    }
}
