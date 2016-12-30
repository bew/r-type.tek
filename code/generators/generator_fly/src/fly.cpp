//
// Created by Pierre Rousselle on 18/11/2016.
//

#include <iostream>
#include "fly.hh"

#include "ECS/Entity.hh"
#include "ECS/CompMusic.hh"
#include "ECS/CompSprite.hh"
#include "ECS/CompSound.hh"
#include "ECS/CompCollision.hh"
#include "ECS/CompCollision.hh"
#include "ECS/CompController.hh"
#include "ECS/CompEvent.hh"
#include "ECS/CompTick.hh"
#include "ECS/CompMovement.hh"
#include "ECS/CompHitbox.hh"
#include "ECS/CompBlueprint.hh"
#include "ECS/CompProjectile.hh"
#include "ECS/CompDamage.hh"
#include "ECS/CompLife.hh"
#include "ECS/CompType.hh"
#include "ECS/CompSuccessor.hh"
#include "ECS/CompDeath.hh"
#include "ECS/CompIA.hh"

const std::string &Empty::getName(void) const {
  return _generator_name;
};

Empty::Empty(void) :
  _generator_name("ROTTEN") {
};

void Empty::update(ECS::WorldData &world) {
  ECS::Component::CompTick *tickc = dynamic_cast<ECS::Component::CompTick *>(world._systemEntity.getComponent(ECS::Component::TICK));
  ECS::Component::CompBlueprint *blueprintsc = dynamic_cast<ECS::Component::CompBlueprint *>(world._systemEntity.getComponent(ECS::Component::BLUEPRINT));

  if (tickc && blueprintsc) {
    if (tickc->tick == 1) {
      logs::logger.registerLogLevel(&logs::assetLogLevel);
      logs::logger.registerBasicsLogLevel();
      
      blueprintsc->blueprints["bloodBurst"] = {
	new ECS::Component::CompMovement({+135, +38}, 20, {1, 0}),
	new ECS::Component::CompSprite("projectileRD", {0, 0}, "default"),
	new ECS::Component::CompHitbox(35, 40),
	new ECS::Component::CompDamage(2),
	new ECS::Component::CompType(ECS::Component::CompType::PROJECTILE),
	new ECS::Component::CompSound("pwee")
      };
      blueprintsc->blueprints["explosion"] = {
	new ECS::Component::CompMovement({0, 0}, 0),
	new ECS::Component::CompSprite("explosion", {0, 0}, "default", {1.0, 1.0}),
	new ECS::Component::CompHitbox(60, 60),
	new ECS::Component::CompDamage(20),
	new ECS::Component::CompType(ECS::Component::CompType::CHARACTER),
	new ECS::Component::CompDeath(23),
	new ECS::Component::CompSound("boom")
      };
      blueprintsc->blueprints["explosionBig"] = {
	new ECS::Component::CompMovement({0, 0}, 0),
	new ECS::Component::CompSprite("explosion", {0, 0}, "default", {2.0, 2.0}),
	new ECS::Component::CompHitbox(120, 120),
	new ECS::Component::CompDamage(20),
	new ECS::Component::CompType(ECS::Component::CompType::CHARACTER),
	new ECS::Component::CompDeath(23),
	new ECS::Component::CompSound("boom")
      };
      blueprintsc->blueprints["organicDeath"] = {
	new ECS::Component::CompMovement({0, 0}, 0),
	new ECS::Component::CompDeath(1),
	new ECS::Component::CompSound("jblurb")
      };
      blueprintsc->blueprints["fly"] = {
	new ECS::Component::CompLife(6, 20),
	new ECS::Component::CompDamage(1),
	new ECS::Component::CompSprite("fly", {0, 0}, "default"),
	new ECS::Component::CompMovement({1350, 360}),
	new ECS::Component::CompHitbox(50, 50),
	new ECS::Component::CompType(ECS::Component::CompType::ENEMY | ECS::Component::CompType::CHARACTER),
	new ECS::Component::CompSuccessor("explosion"),
	new ECS::Component::CompIA("sin")
      };
      world._systemEntity.addComponent(new ECS::Component::CompSprite("desert", {1280/2, 720/2}));
      
      for (ECS::Entity::Entity *entity : world._gameEntities) {
	if (entity->getId() >= 1 && entity->getId() <= 4) {
	   entity->addComponent(new ECS::Component::CompLife(5, 25));
	   entity->addComponent(new ECS::Component::CompSprite("wasp"));
	   entity->addComponent(new ECS::Component::CompMovement({100, 720 / 5 * entity->getId()}));
	   entity->addComponent(new ECS::Component::CompHitbox(120, 60));
	   entity->addComponent(new ECS::Component::CompProjectile("bloodBurst"));
	   entity->addComponent(new ECS::Component::CompSuccessor("explosionBig"));
	}
      }
    }
    if (!(tickc->tick % 90)) {
      try {
	world._gameEntities.push_back(blueprintsc->spawn("fly"));
      }
      catch (const ECS::Component::ComponentFlagException &e) {
	logs::logger[logs::ERRORS] << "Cannot clone '" << "fly" << "' : '" << e.what() << "'" << std::endl;
      }
    }
  }
}

EXPORT(Empty);
