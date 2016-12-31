/**
 * @file main.cpp
 * @author Nekhot.
 * @brief Dummy main for client. Create an ecs loop with a windowComponent
 */
#include <iostream>
#include "SysWindow.hh"
#include "CompWindow.hh"
#include "SysAsset.hh"
#include "CompAsset.hh"
#include "SysMusic.hh"
//Client sound, not server one
#include "CompSound.hh"
#include "SysSound.hh"
#include "SysSprite.hh"
#include "CompOptions.hh"
#include "SysKeyboard.hh"
#include "SysOptions.hh"
#include "SysGui.hh"

#include "ECS/CompScore.hh"
#include "ECS/CompMusic.hh"
#include "ECS/CompSprite.hh"
#include "ECS/CompCollision.hh"
#include "ECS/SysController.hh"
#include "ECS/SysCollision.hh"
#include "ECS/CompCollision.hh"
#include "ECS/CompController.hh"
#include "ECS/CompEvent.hh"
#include "ECS/SysEvent.hh"
#include "ECS/CompTick.hh"
#include "ECS/SysTick.hh"
#include "ECS/CompMovement.hh"
#include "ECS/SysMovement.hh"
#include "ECS/SysCollision.hh"
#include "ECS/CompHitbox.hh"
#include "ECS/CompBlueprint.hh"
#include "ECS/CompProjectile.hh"
#include "ECS/CompDamage.hh"
#include "ECS/CompLife.hh"
#include "ECS/SysDeath.hh"
#include "ECS/SysLife.hh"
#include "ECS/SysDamage.hh"
#include "ECS/CompType.hh"
#include "ECS/CompSuccessor.hh"
#include "ECS/SysIA.hh"

#include "LibraryLoader/CompGenerator.hh"
#include "LibraryLoader/SysGenerator.hh"

#include "SysMenu.hh"

int main(int ac, char**av) {

  ECS::World world;
  
//  logs::getLogger().registerLogLevel(&logs::assetLogLevel);
//  logs::getLogger().registerBasicsLogLevel();
//
//  ////////////////////////// ADD SYSTEMS TO WORLD
//
//  // control time, Has absolut priority over any other system
//  world.addSystem(new ECS::System::SysTick());
//  // control time, Has absolut priority over any other system /////////// SERVER EMULATION
//  world.addSystem(new ECS::System::SysGenerator());
//  // process options (read/write/events). Should be initilized before system that use options to avoid doing the same things multiple things
//  world.addSystem(new ECS::System::SysOptions());
//  // open, reopen, clear and display window. Should be initilized before running system that draw things
//  world.addSystem(new ECS::System::SysWindow());
//  // transform input to data(up, down, fire, left, right)
//  world.addSystem(new ECS::System::SysKeyboard());   // CLIENT
//  // transform data to movement (speed, direction)
//  world.addSystem(new ECS::System::SysController());
//  // update movement speed, direction for computer controlled entity
//  world.addSystem(new ECS::System::SysIA());
//  // transform movement to  movement(position)
//  world.addSystem(new ECS::System::SysMovement());
//  // Analyze collision, fill compCollision
//  world.addSystem(new ECS::System::SysCollision());
//  // Initilize and update assets stores
//  world.addSystem(new ECS::System::SysAsset());      // CLIENT
//  // do something sometimes
//  world.addSystem(new ECS::System::SysMusic());      // CLIENT
//   // do something sometimes
//  world.addSystem(new ECS::System::SysSound());      // CLIENT
//  // put sprite onto window surface
//  world.addSystem(new ECS::System::SysSprite());     // CLIENT
//   // put gui onto window surface
//  world.addSystem(new ECS::System::SysGui());        // CLIENT
//  // process collision and apply damage
//  world.addSystem(new ECS::System::SysDamage());
//   // process life and apply death
//  world.addSystem(new ECS::System::SysLife());
//  // process entity and remove the dead ones
//  world.addSystem(new ECS::System::SysDeath());
//  // process events that happen in the tick
//  world.addSystem(new ECS::System::SysEvent());
//
//  ///////////////////////// ADD UNIQUE COMPONENTS TO WORLD
//
//  ECS::Component::CompGenerator *generator = new ECS::Component::CompGenerator();                // SERVER EMULATION
//  ECS::Component::CompBlueprint *blueprints = new ECS::Component::CompBlueprint();               // SERVER EMULATION
//  ECS::Component::CompTick *tick = new ECS::Component::CompTick();
//  ECS::Component::CompEvent *event = new ECS::Component::CompEvent();
//
//  // SERVER EMULATION
//  try {
//    #ifdef _WIN32
//    std::shared_ptr<LibraryLoader> module(new LibraryLoader("./generators/fly.dll"));
//    #else
//    std::shared_ptr<LibraryLoader> module(new LibraryLoader("./generators/libfly.so"));
//    #endif
//    Dependent_ptr<IGenerator, LibraryLoader> generatorRef(module->newInstance(), module);
//    generator->generator = generatorRef;
//  } catch (const LibraryLoaderException &e) {
//    logs::getLogger()[logs::ERRORS] << e.what() << std::endl;
//  }
//  world.addSystemEntityComponent(generator);
//  world.addSystemEntityComponent(blueprints);
//  //
//  world.addSystemEntityComponent(tick);
//  world.addSystemEntityComponent(new ECS::Component::CompWindow());
//  world.addSystemEntityComponent(event);
//  world.addSystemEntityComponent(new ECS::Component::CompOptions());
//  world.addSystemEntityComponent(new ECS::Component::CompAsset());
//  world.addSystemEntityComponent(new ECS::Component::CompCollision());
//  world.addSystemEntityComponent(new ECS::Component::CompScore(0));
//
//  ///////////////////////// INITIALIZE PLAYER (id 1 to 4 are reserved to players)
//
//  ECS::Entity::Entity *entity = new ECS::Entity::Entity(1); //Server emulation here, we don't what will be our id
//  entity->addComponent(new ECS::Component::CompController());
//  entity->addComponent(new ECS::Component::CompType(ECS::Component::CompType::PLAYER | ECS::Component::CompType::CHARACTER));
//
//  world._world._gameEntities.push_back(entity);

  //////////////////////// RUN THE WORLD

//  while (!tick->kill) {
//    world.update();
//  }


  world.addSystem(new ECS::System::SysTick());
  world.addSystem(new ECS::System::SysOptions());
  world.addSystem(new ECS::System::SysWindow());
  world.addSystem(new ECS::System::SysMenu());

  world.addSystemEntityComponent(new ECS::Component::CompWindow());
  world.addSystemEntityComponent(new ECS::Component::CompOptions());
  world.addSystemEntityComponent(new ECS::Component::CompTick());

  while (true) {
    world.update();
  }
  return 0;
}
