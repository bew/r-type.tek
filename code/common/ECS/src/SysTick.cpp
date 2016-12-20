/**
 * @file SysTick.cpp
 * @author Nekhot.
 * @brief Impelmentation of system procesing tick.
 */
#include <iostream>
#include "SysTick.hh"
#include "CompEvent.hh"

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
	  if (tickc->tick = =1) {
	    Component::CompEvent *eventc = dynamic_cast<Component::CompEvent*>(world._systemEntity.getComponent(Component::EVENT));
	    if (eventc)
	      eventc->addEvent("initialized", nullptr);
	  }
	  tickc->current = std::chrono::high_resolution_clock::now();
	  std::this_thread::sleep_for(tickc->tickDuration - (tickc->current - tickc->previous));
	  tickc->previous = std::chrono::high_resolution_clock::now();
	}
	++tickc->tick;
      }
    }
  }
}
