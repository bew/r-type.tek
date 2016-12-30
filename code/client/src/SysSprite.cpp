/**
 * @file SysSprite.cpp
 * @author Nekhot
 * @brief Impelmentation of system procesing sprite.
 */

#include "SysSprite.hh"

namespace ECS {
  namespace System {

    void SysSprite::update(ECS::Entity::Entity *entity, WorldData &world) { 
      Component::CompSprite *spritec = dynamic_cast<Component::CompSprite*>(entity->getComponent(ECS::Component::SPRITE));
      Component::CompMovement *movementc = dynamic_cast<Component::CompMovement*>(entity->getComponent(ECS::Component::MOVEMENT));
      Component::CompAsset *assetc = dynamic_cast<Component::CompAsset*>(world._systemEntity.getComponent(ECS::Component::STANDARD_ASSET));
      Component::CompWindow *windowc = dynamic_cast<Component::CompWindow*>(world._systemEntity.getComponent(ECS::Component::WINDOW));
      Component::CompLife *lifec = dynamic_cast<Component::CompLife*>(entity->getComponent(ECS::Component::LIFE));
      Component::CompTick *tickc = dynamic_cast<Component::CompTick*>(world._systemEntity.getComponent(ECS::Component::TICK));
      coordinates<int> position(0, 0);
      
      if (!windowc || !windowc->window || !assetc)
	return ;
      if (movementc)
	position = movementc->_coo;      
      if (spritec) {
	try {
	  sf::Sprite sprite;
	  if (spritec->animation == Component::CompSprite::NO_ANIMATION)
	    sprite.setTexture(assetc->store.getSprite(spritec->name).getLowLevelTexture());
	  else {
	    try {
	      graphic::AnimatedSpriteAsset::FrameDescriptions animations = assetc->store.getAnimatedSprite(spritec->name).getAnimations().at(spritec->animation);
	      
	      sprite.setTexture(assetc->store.getAnimatedSprite(spritec->name).getLowLevelTexture());
	      if (spritec->animationTick == -1)
		spritec->animationTick = tickc->tick;
	      sprite.setTextureRect(animations.frames[(tickc->tick - spritec->animationTick) % (animations.frames.size() * animations.frequency) / animations.frequency]);
	    }
	    catch (const std::out_of_range &e) {
	      logs::getLogger()[logs::ASSET] << "Animation '" << spritec->animation << "' doesn't exist for sprite '" << spritec->name << "'" << std::endl;
	    }
	  }
	  sprite.setScale(spritec->scale._x, spritec->scale._y);
	  sprite.setPosition(position._x - (sprite.getTextureRect().width * spritec->scale._x / 2) + spritec->center._x,
			     position._y - (sprite.getTextureRect().height * spritec->scale._y / 2) + spritec->center._y);
	  if (lifec && lifec->lastDamageTick != -1 && tickc->tick - lifec->lastDamageTick < lifec->postDamageInvincibility && lifec->postDamageInvincibility) {
	    int modulation = (tickc->tick - lifec->lastDamageTick) * 256 / lifec->postDamageInvincibility;
	    sprite.setColor(sf::Color(modulation, 0, 0));
	  }
	  windowc->window->draw(sprite);
	} catch (const graphic::AssetException &e) {
	  logs::getLogger()[logs::ASSET] << e.what() << std::endl;
	}
      }
    }
    
    void SysSprite::update(WorldData &world) {
      this->update(&world._systemEntity, world);
      for (ECS::Entity::Entity *entity : world._gameEntities) {
	this->update(entity, world);
      }
    }
  }
}
