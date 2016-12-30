/**
 * @file SysWindow.cpp
 * @author Nekhot.
 * @brief Impelmentation of system procesing windows.
 */
#include <iostream>
#include "SysMusic.hh"

namespace ECS {
  namespace System {

    void SysMusic::update(WorldData &world) {
      Component::CompMusic *musicc = dynamic_cast<Component::CompMusic*>(world._systemEntity.getComponent(ECS::Component::MUSIC));
      Component::CompAsset *assetc = dynamic_cast<Component::CompAsset*>(world._systemEntity.getComponent(ECS::Component::STANDARD_ASSET));
      Component::CompOptions *optionsc = dynamic_cast<Component::CompOptions*>(world._systemEntity.getComponent(ECS::Component::OPTIONS));
      
      if (musicc && assetc && optionsc) {
	try {
	  sf::Music &llm = assetc->store.getMusic(musicc->getMusic()).getLowLevelMusic();
	  if (llm.getStatus() == sf::SoundSource::Stopped) {
	    llm.setVolume(optionsc->getMusicVolume());
	    llm.play();
	  }
	}
	catch (const graphic::AssetException &e) {
	  logs::getLogger()[logs::ASSET] << e.what() << std::endl;
	}
      }
    }
  }
}
