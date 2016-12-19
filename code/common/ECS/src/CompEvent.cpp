/**
 * @file CompEvent.cpp
 * @author Nekhot.
 * @brief Implementation for component events.
 *
 */

#include "CompEvent.hh"

namespace ECS {
    namespace Component {

      CompEvent::IEvent::~IEvent(void)
      {
      }
      
      CompEvent::CompEvent(void) : AComponent("event")
      {
      }
    }
}

