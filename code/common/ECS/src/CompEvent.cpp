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
    {}

    CompEvent::CompEvent(void) : AComponent("event"), locked(false)
    {}

    void CompEvent::addHook(const std::string &eventName, std::function<bool(IEvent*)> hook) {
      _hooks.emplace(eventName, hook);
    }

    void CompEvent::addEvent(const std::string &eventName, IEvent *event) {
      if (locked)
	_nextTickEvents.emplace(eventName, event);
      else
	_events.emplace(eventName, event);
    };

    void CompEvent::addSameTickEvent(const std::string &eventName, IEvent *event) {
      _sameTickEvents.emplace(eventName, event);
    };
  }
}
