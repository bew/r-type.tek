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
	  sf::Text score(std::string("SCORE : ") + std::to_string(scorec->score), assetc->store.getFont("gui").getLowLevelFont());
	  score.setPosition(20.0, 20.0);
	  windowc->window->draw(score);
	} catch (const graphic::AssetException &e) {
          logs::getLogger()[logs::ASSET] << e.what() << std::endl;
        }
      }
    }
  }
}
