/**
 * @file SysEvent.cpp
 * @author Nekhot.
 * @brief Impelmentation of system procesing events.
 */

#include <iostream>
#include "SysEvent.hh"

namespace ECS {
  namespace System {

    void SysEvent::update(WorldData &world) {
      Component::CompEvent *eventc;
      eventc = dynamic_cast<Component::CompEvent*>(world._systemEntity.getComponent("event"));
      if (eventc)
	eventc->locked = true;

      for (Entity::Entity *entity : world._gameEntities) {
	Component::CompEvent *eventc;
	eventc = dynamic_cast<Component::CompEvent*>(entity->getComponent("event"));
	if (eventc)
	  eventc->locked = true;
      }
      update(world._systemEntity);
      for (Entity::Entity *entity : world._gameEntities) {
	update(*entity);
      }
      eventc = dynamic_cast<Component::CompEvent*>(world._systemEntity.getComponent("event"));
      if (eventc)
	eventc->locked = false;
      for (Entity::Entity *entity : world._gameEntities) {
	Component::CompEvent *eventc = dynamic_cast<Component::CompEvent*>(entity->getComponent("event"));
	if(eventc)
	  eventc->locked = false;
      }
    }

    void SysEvent::update(Entity::Entity &entity) {
      Component::CompEvent *eventc = dynamic_cast<Component::CompEvent*>(entity.getComponent("event"));
      if (eventc) {

        for (auto ievent = eventc->_events.begin(); ievent != eventc->_events.end(); ievent++) {
	  auto range = eventc->_hooks.equal_range((*ievent).first);
	  for (auto ihook = range.first; ihook != range.second;) {
	    if (!(*ihook).second((*ievent).second)) {
	      eventc->_hooks.erase(ihook++);
	    }
	    else
	      ++ihook;
	  }
        }
	eventc->_events.clear();

	while (eventc->_sameTickEvents.size()) {
	  for (auto ievent = eventc->_sameTickEvents.begin(); ievent != eventc->_sameTickEvents.end(); ievent++) {
	    auto range = eventc->_hooks.equal_range((*ievent).first);
	    for (auto ihook = range.first; ihook != range.second;) {
	      if (!(*ihook).second((*ievent).second)) {
		eventc->_hooks.erase(ihook++);
	      }
	      else
		++ihook;
	    }
	  }
	}
	
        eventc->_events = eventc->_nextTickEvents;
	eventc->_nextTickEvents.clear();
      }
    }
  }
}
