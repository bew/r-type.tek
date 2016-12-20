/**
 * @file SysTick.cpp
 * @author Nekhot.
 * @brief Impelmentation of system procesing tick.
 */
#include <iostream>
#include "SysTick.hh"

namespace ECS {
  namespace System {
    void SysTick::update(WorldData &world) {      
      Component::CompTick *tickc = dynamic_cast<Component::CompTick*>(world._systemEntity.getComponent(Component::TICK));
      if (tickc) {
	if (!tickc->tick) {
	  tickc->start = std::chrono::high_resolution_clock::now();
	  tickc->previous = tickc->start;
	  tickc->current = tickc->start;
	} else {
	  tickc->current = std::chrono::high_resolution_clock::now();
	  std::this_thread::sleep_for(tickc->tickDuration - (tickc->current - tickc->previous));
	  tickc->previous = std::chrono::high_resolution_clock::now();
	}
	++tickc->tick;
      }
    }
  }
}
