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
      Entity::Entity *player = (world._gameEntities.size() ? world._gameEntities[0] : nullptr);
      
      if (windowc && windowc->window && assetc && scorec) {
	try {
	  std::string scoreString = std::string("SCORE : ") + std::to_string(scorec->score);
	  if (player && player->getId() == 1) {//not sure...
	    Component::CompLife *lifec = dynamic_cast<Component::CompLife*>(player->getComponent(ECS::Component::LIFE));
	    if (lifec)
	      scoreString += "  LIFE : " + std::to_string(lifec->getCurrentLife());
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
