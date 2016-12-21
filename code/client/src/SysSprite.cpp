/**
 * @file SysSprite.cpp
 * @author Nekhot
 * @brief Impelmentation of system procesing sprite.
 */

#include "SysSprite.hh"

namespace ECS {
  namespace System {

    void SysSprite::update(WorldData &world) {

      //Chercher dans le Store du ganarator !
      Component::CompAsset *assetc = dynamic_cast<Component::CompAsset*>(world._systemEntity.getComponent(ECS::Component::STANDARD_ASSET));
      Component::CompWindow *windowc = dynamic_cast<Component::CompWindow*>(world._systemEntity.getComponent(ECS::Component::WINDOW));
      Component::CompSprite *spritec;
      Component::CompMovement *movementc;
      
      if (windowc && windowc->window && assetc && movementc) {
	for (ECS::Entity::Entity *entity : world._gameEntities) {
	  spritec = dynamic_cast<Component::CompSprite*>(entity->getComponent(ECS::Component::SPRITE));
	  movementc = dynamic_cast<Component::CompMovement*>(entity->getComponent(ECS::Component::MOVEMENT));
	  if (spritec && movementc) {
	    try {
	      sf::Sprite sprite(assetc->store.getSprite(spritec->name).getLowLevelTexture());
	      sprite.setPosition(movementc->_coo._x - (sprite.getTextureRect().width / 2) + spritec->center._x,
				 movementc->_coo._y - (sprite.getTextureRect().height / 2) + spritec->center._y);
	      windowc->window->draw(sprite);
	    } catch (const graphic::AssetException &e) {
	      std::cerr << e.what() << std::endl;
	    }
	  }
	}
      }
    }
  }
}

