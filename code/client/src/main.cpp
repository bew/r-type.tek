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
  ECS::System::SysSerialisation::builders[ECS::Component::DAMAGE] = &ECS::Component::AComponent::factory<ECS::Component::CompDamage>;
  ECS::System::SysSerialisation::builders[ECS::Component::IA] = &ECS::Component::AComponent::factory<ECS::Component::CompIA>;
  ECS::System::SysSerialisation::builders[ECS::Component::SCORE] = &ECS::Component::AComponent::factory<ECS::Component::CompScore>;
  ECS::System::SysSerialisation::builders[ECS::Component::TYPE] = &ECS::Component::AComponent::factory<ECS::Component::CompType>;
  ECS::System::SysSerialisation::builders[ECS::Component::HITBOX] = &ECS::Component::AComponent::factory<ECS::Component::CompHitbox>;
  ECS::System::SysSerialisation::builders[ECS::Component::DEATH] = &ECS::Component::AComponent::factory<ECS::Component::CompDeath>;
  
  ECS::World world;
  
  logs::getLogger().registerLogLevel(&logs::assetLogLevel);
  logs::getLogger().registerBasicsLogLevel();
  
  world.addSystem(new ECS::System::SysTick());
  world.addSystem(new ECS::System::SysOptions());
  world.addSystem(new ECS::System::SysWindow());
  world.addSystem(new ECS::System::SysStateMachine());
  world.addSystem(new ECS::System::SysGenerator());
  world.addSystem(new ECS::System::SysSerialisation());
  world.addSystem(new ECS::System::SysKeyboard());
  world.addSystem(new ECS::System::SysController());
  world.addSystem(new ECS::System::SysIA());
  world.addSystem(new ECS::System::SysMovement());
  world.addSystem(new ECS::System::SysCollision());
  world.addSystem(new ECS::System::SysAsset());
  world.addSystem(new ECS::System::SysMenu());
  world.addSystem(new ECS::System::SysMusic());
  world.addSystem(new ECS::System::SysSound());
  world.addSystem(new ECS::System::SysSprite());
  world.addSystem(new ECS::System::SysDamage());
  world.addSystem(new ECS::System::SysLife());
  world.addSystem(new ECS::System::SysDeath());
  world.addSystem(new ECS::System::SysEvent());

  ECS::Component::CompTick *tick = new ECS::Component::CompTick();  
  world.addSystemEntityComponent(tick);
  world.addSystemEntityComponent(new ECS::Component::CompWindow());
  world.addSystemEntityComponent(new ECS::Component::CompEvent());
  world.addSystemEntityComponent(new ECS::Component::CompOptions());
  world.addSystemEntityComponent(new ECS::Component::CompAsset());
  world.addSystemEntityComponent(new ECS::Component::CompStateMachine());
  world.addSystemEntityComponent(new ECS::Component::CompLogin());
  world.addSystemEntityComponent(new ECS::Component::CompNetworkClient());
  
  while (!tick->kill) {
    world.update();
  }
  return 0;
}
