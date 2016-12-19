/**
 * @file main.cpp
 * @author Nekhot.
 * @brief Dummy main for client. Create an ecs loop with a windowComponent
 */

#include <iostream>
#include "SysWindow.hh"
#include "CompWindow.hh"
#include "ECS/CompEvent.hh"
#include "ECS/SysEvent.hh"
#include "Graphic/AssetStore.hpp"

int main(void) {

  ECS::World world;
  graphic::GroupedAssetStore test("asset", "test");
  world.addSystem(new ECS::System::SysWindow());
  world.addSystem(new ECS::System::SysEvent());
  world.addSystemEntityComponent(new ECS::Component::CompWindow());
  ECS::Component::CompEvent *events = new ECS::Component::CompEvent();
  world.addSystemEntityComponent(events);

  events->addHook("TEST_EVENT", [&events](ECS::Component::CompEvent::IEvent *e) {
      std::cout << "Salut, je suis une evenement." << std::endl;
      return true;
    });

  events->addHook("TEST_EVENT_THAT_REPEAT_ITSELF_BUT_HOOK_RETURN_FALSE", [&events](ECS::Component::CompEvent::IEvent *e) {
      std::cout << "Salut, je suis une evenement qui se repete a l'infini, mais mon hook return false donc il s'autodetruit, plus rien ne peut m'appeler et je disparais." << std::endl;
      events->addEvent("TEST_EVENT_THAT_REPEAT_ITSELF_BUT_HOOK_RETURN_FALSE", nullptr);
      return false;
    });
  
  class THREE_TIME_EVENT : public ECS::Component::CompEvent::IEvent {
  public:
    THREE_TIME_EVENT(void) : count(0) {};
    int count;
  };

  events->addHook("TEST_EVENT_THAT_REPEAT_ITSELF_THREE_TIME", [&events](ECS::Component::CompEvent::IEvent *e) {
      std::cout << "Salut, je suis une evenement. Je vais me repeter trois fois." << std::endl;
      THREE_TIME_EVENT *te = dynamic_cast<THREE_TIME_EVENT *>(e);
      if (te->count < 3) {
	++te->count;
	events->addEvent("TEST_EVENT_THAT_REPEAT_ITSELF_THREE_TIME", te);
	return true;
      }
      else 
	return false;
    });


  events->addEvent("TEST_EVENT", nullptr);
  events->addEvent("TEST_EVENT_THAT_REPEAT_ITSELF_BUT_HOOK_RETURN_FALSE", nullptr);
  events->addEvent("TEST_EVENT_THAT_REPEAT_ITSELF_THREE_TIME", new THREE_TIME_EVENT());

  // These two event don't have hook, so they will be flushed without anything happening.
  events->addEvent("TEST_EVENT2", nullptr);
  events->addEvent("TEST_EVENT3", nullptr);
  
  while(true) {
    world.update();
  }
  return 0;
};
