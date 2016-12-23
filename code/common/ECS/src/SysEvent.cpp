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
            eventc = dynamic_cast<Component::CompEvent *>(world._systemEntity.getComponent(ECS::Component::EVENT));
            if (eventc)
                eventc->locked = true;

      for (Entity::Entity *entity : world._gameEntities) {
	Component::CompEvent *eventc;
	eventc = dynamic_cast<Component::CompEvent*>(entity->getComponent(ECS::Component::EVENT));
	if (eventc)
	  eventc->locked = true;
      }
#ifdef _WIN32
      updateW(world._systemEntity, world);
      for (Entity::Entity *entity : world._gameEntities) {
	updateW(*entity, world);
      }
#else
      update(world._systemEntity, world);
      for (Entity::Entity *entity : world._gameEntities) {
	update(*entity, world);
      }
#endif
      eventc = dynamic_cast<Component::CompEvent*>(world._systemEntity.getComponent(ECS::Component::EVENT));
      if (eventc)
	eventc->locked = false;
      for (Entity::Entity *entity : world._gameEntities) {
	Component::CompEvent *eventc = dynamic_cast<Component::CompEvent*>(entity->getComponent(ECS::Component::EVENT));
	if (eventc)
	  eventc->locked = false;
      }
    }

    void SysEvent::updateW(Entity::Entity &entity, WorldData &world) {
      Component::CompEvent *eventc = dynamic_cast<Component::CompEvent*>(entity.getComponent(ECS::Component::EVENT));
      if (eventc) {

	std::unordered_multimap<std::string, ECS::Component::CompEvent::EventHandler> hooksToKeep;

	for (auto ievent = eventc->_events.begin(); ievent != eventc->_events.end(); ievent++) {
	  auto range = eventc->_hooks.equal_range((*ievent).first);
	  for (auto ihook = range.first; ihook != range.second;) {

	    if ((*ihook).second((*ievent).second, world))
	      hooksToKeep.emplace((*ihook).first, (*ihook).second);
	    ++ihook;
	  }
	  delete (*ievent).second;
	  for (auto hookToKeep : hooksToKeep)
	    eventc->_hooks.emplace(hookToKeep.first, hookToKeep.second);
	  hooksToKeep.clear();
	}
	eventc->_events.clear();

	while (eventc->_sameTickEvents.size()) {
	  for (auto ievent = eventc->_sameTickEvents.begin(); ievent != eventc->_sameTickEvents.end(); ievent++) {
	    auto range = eventc->_hooks.equal_range((*ievent).first);
	    for (auto ihook = range.first; ihook != range.second;) {
	      if ((*ihook).second((*ievent).second, world))
		hooksToKeep.emplace((*ihook).first, (*ihook).second);
	      ++ihook;
	    }
	    delete (*ievent).second;
	    for (auto hookToKeep : hooksToKeep)
	      eventc->_hooks.emplace(hookToKeep.first, hookToKeep.second);
	    hooksToKeep.clear();
	    ievent = eventc->_sameTickEvents.erase(ievent);
	  }
	}

	eventc->_events = eventc->_nextTickEvents;
	eventc->_nextTickEvents.clear();
      }
    }



    void SysEvent::update(Entity::Entity &entity, WorldData &world) {
      Component::CompEvent *eventc = dynamic_cast<Component::CompEvent*>(entity.getComponent(ECS::Component::EVENT));
      if (eventc) {
	for (auto ievent = eventc->_events.begin(); ievent != eventc->_events.end(); ievent++) {
	  auto range = eventc->_hooks.equal_range((*ievent).first);
	  for (auto ihook = range.first; ihook != range.second;) {

	    if (!(*ihook).second((*ievent).second, world)) {
	      ihook = eventc->_hooks.erase(ihook);
	    }
	    else
	      ++ihook;
	    delete (*ievent).second;
	  }
	}
	eventc->_events.clear();

	while (eventc->_sameTickEvents.size()) {
	  for (auto ievent = eventc->_sameTickEvents.begin(); ievent != eventc->_sameTickEvents.end(); ievent++) {
	    auto range = eventc->_hooks.equal_range((*ievent).first);
	    for (auto ihook = range.first; ihook != range.second;) {
	      if (!(*ihook).second((*ievent).second, world)) {
		ihook = eventc->_hooks.erase(ihook);
	      }
	      else
		++ihook;
	      delete (*ievent).second;
	    }
	    ievent = eventc->_sameTickEvents.erase(ievent);
	  }
	}

	eventc->_events = eventc->_nextTickEvents;
	eventc->_nextTickEvents.clear();
      }
    }
}
