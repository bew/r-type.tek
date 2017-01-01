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
#include "CompSound.hh"
#include "SysSound.hh"
#include "SysSprite.hh"
#include "CompOptions.hh"
#include "SysKeyboard.hh"
#include "SysOptions.hh"
#include "SysSerialisation.hh"
#include "CompNetworkClient.hh"
#include "SysStateMachine.hh"
#include "CompStateMachine.hh"
#include "CompLogin.hh"

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
  
  ECS::System::SysSerialisation::builders[ECS::Component::MOVEMENT] = &ECS::Component::AComponent::factory<ECS::Component::CompMovement>;
  ECS::System::SysSerialisation::builders[ECS::Component::SPRITE] = &ECS::Component::AComponent::factory<ECS::Component::CompSprite>;
  ECS::System::SysSerialisation::builders[ECS::Component::CONTROLLER] = &ECS::Component::AComponent::factory<ECS::Component::CompController>;
  
  ECS::World world;
  
  logs::getLogger().registerLogLevel(&logs::assetLogLevel);
  logs::getLogger().registerBasicsLogLevel();
  
  ////////////////////////// ADD SYSTEMS TO WORLD

  // control time, Has absolut priority over any other system
  world.addSystem(new ECS::System::SysTick());
  // process options (read/write/events). Should be initilized before system that use options to avoid doing the same things multiple things
  world.addSystem(new ECS::System::SysOptions());
  // open, reopen, clear and display window. Should be initilized before running system that draw things
  world.addSystem(new ECS::System::SysWindow());
  // Handle client state
  world.addSystem(new ECS::System::SysStateMachine());
  // Handle network
  world.addSystem(new ECS::System::SysSerialisation());   // CLIENT
  // transform input to data(up, down, fire, left, right)
  world.addSystem(new ECS::System::SysKeyboard());        // CLIENT
  // transform data to movement (speed, direction)
  world.addSystem(new ECS::System::SysController());
  // update movement speed, direction for computer controlled entity
  world.addSystem(new ECS::System::SysIA());
  // transform movement to  movement(position)
  world.addSystem(new ECS::System::SysMovement());
  // Analyze collision, fill compCollision
  world.addSystem(new ECS::System::SysCollision());
  // Initilize and update assets stores
  world.addSystem(new ECS::System::SysAsset());      // CLIENT
  // Handle menu operations
  world.addSystem(new ECS::System::SysMenu());      // CLIENT
  // do something sometimes
  world.addSystem(new ECS::System::SysMusic());      // CLIENT
  // do something sometimes
  world.addSystem(new ECS::System::SysSound());      // CLIENT
  // put sprite onto window surface
  world.addSystem(new ECS::System::SysSprite());     // CLIENT
  // process collision and apply damage
  world.addSystem(new ECS::System::SysDamage());
  // process life and apply death
  world.addSystem(new ECS::System::SysLife());
  // process entity and remove the dead ones
  world.addSystem(new ECS::System::SysDeath());
  // process events that happen in the tick
  world.addSystem(new ECS::System::SysEvent());

  ///////////////////////// ADD UNIQUE COMPONENTS TO WORLD

  ECS::Component::CompTick *tick = new ECS::Component::CompTick();
  
  world.addSystemEntityComponent(tick);
  world.addSystemEntityComponent(new ECS::Component::CompWindow());
  world.addSystemEntityComponent(new ECS::Component::CompEvent());
  world.addSystemEntityComponent(new ECS::Component::CompOptions());
  world.addSystemEntityComponent(new ECS::Component::CompAsset());
  world.addSystemEntityComponent(new ECS::Component::CompStateMachine());
  world.addSystemEntityComponent(new ECS::Component::CompLogin());
  try {
    world.addSystemEntityComponent(new ECS::Component::CompNetworkClient("rtpe.paccard.info", 42403));
  }
  catch (network::SocketException &e) {
    logs::getLogger()[logs::ERRORS] << "Unable to connect to server '" << e.what() << "'" << std::endl;
    return 1;
  }
  
  while (!tick->kill) {
    world.update();
  }
  return 0;
}
