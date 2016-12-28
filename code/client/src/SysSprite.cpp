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
	    Component::CompTick *tickc = dynamic_cast<Component::CompTick*>(world._systemEntity.getComponent(ECS::Component::TICK));
	    try {
	      graphic::AnimatedSpriteAsset::FrameDescriptions animations = assetc->store.getAnimatedSprite(spritec->name).getAnimations().at(spritec->animation);
	      
	      sprite.setTexture(assetc->store.getAnimatedSprite(spritec->name).getLowLevelTexture());
	      sprite.setTextureRect(animations.frames[tickc->tick % (animations.frames.size() * animations.frequency) / animations.frequency]);
	    }
	    catch (const std::out_of_range &e) {
	      logs::logger[logs::ASSET] << "Animation '" << spritec->animation << "' doesn't exist for sprite '" << spritec->name << "'" << std::endl;
	    }
	  }
	  sprite.setPosition(position._x - (sprite.getTextureRect().width / 2) + spritec->center._x,
			     position._y - (sprite.getTextureRect().height / 2) + spritec->center._y);
	  windowc->window->draw(sprite);
	} catch (const graphic::AssetException &e) {
	  logs::logger[logs::ASSET] << e.what() << std::endl;
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
