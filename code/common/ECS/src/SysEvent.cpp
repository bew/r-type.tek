/**
 * @file SysWindow.cpp
 * @author Nekhot.
 * @brief Impelmentation of system procesing windows.
 */

#include "SysEvent.hh"

namespace ECS {
  namespace System {

    void SysWindow::update(WorldData &world) {
      update(world._systemEntity);
      for (Entity &entity : world._gameEntities)
	update(*entity);
    }

    void SysWindow::update(Entity::Entity &entity) {
      Component::CompEvent *eventc = dynamic_cast<Component::CompEvent*>(entity.getComponent("event"));
      if (eventc) {
	for (std::pair<std::string, IEvent *> event : eventc->_events) {
	  auto range = eventc->_hooks.equal_range(event.first);
	  for (std::pair<std::string, std::function<bool(IEvent*)>> ihook = range.first; ihook < range.second; ihook++)
	    if (!(*ihook).second(event.second))
	      eventc->_hooks.erase(ihook);
	}
	eventc->_events.clear();
      }
    }
  }
}
