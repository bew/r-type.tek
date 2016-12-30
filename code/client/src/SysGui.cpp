/**
 * @file SysSprite.cpp
 * @author Nekhot
 * @brief Impelmentation of system procesing sprite.
 */

#include "SysGui.hh"

namespace ECS {
  namespace System {
    
    void SysGui::update(WorldData &world) {
      Component::CompAsset *assetc = dynamic_cast<Component::CompAsset*>(world._systemEntity.getComponent(ECS::Component::STANDARD_ASSET));
      Component::CompWindow *windowc = dynamic_cast<Component::CompWindow*>(world._systemEntity.getComponent(ECS::Component::WINDOW));
      Component::CompScore *scorec = dynamic_cast<Component::CompScore*>(world._systemEntity.getComponent(ECS::Component::SCORE));
     
      if (windowc && windowc->window && assetc && scorec) {
	try {
	  std::string scoreString = std::string("SCORE : ") + std::to_string(scorec->score);

	  for (ECS::Entity::Entity *entity : world._gameEntities) {
	    if (entity->getId() >= 1 && entity->getId() <= 4) {
	      Component::CompLife *lifec = dynamic_cast<Component::CompLife*>(entity->getComponent(ECS::Component::LIFE));
	      if (lifec)
		scoreString += "   P" + std::to_string(entity->getId()) + " LIFE : " + std::to_string(lifec->getCurrentLife());
	    }
	  }
	  sf::Text score(scoreString, assetc->store.getFont("gui").getLowLevelFont());
	  score.setPosition(20.0, 20.0);
	  windowc->window->draw(score);
	} catch (const graphic::AssetException &e) {
          logs::getLogger()[logs::ASSET] << e.what() << std::endl;
        }
      }
    }
  }
}
