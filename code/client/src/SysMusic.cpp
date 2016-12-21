/**
 * @file SysWindow.cpp
 * @author Nekhot.
 * @brief Impelmentation of system procesing windows.
 */

#include "SysMusic.hh"

namespace ECS {
  namespace System {

    void SysMusic::update(WorldData &world) {
      Component::CompMusic *musicc = dynamic_cast<Component::CompMusic*>(world._systemEntity.getComponent(ECS::Component::MUSIC));
      Component::CompAsset *assetc = dynamic_cast<Component::CompAsset*>(world._systemEntity.getComponent(ECS::Component::STANDARD_ASSET));
      if (musicc && musicc->name != "" && assetc && assetc->store) {
	try {
	  sf::Music &music = assetc->store->getMusic(musicc->name).getLowLevelMusic();
	  if (music.getStatus() == sf::SoundSource::Playing && !musicc->playing) {
	    music.stop();
	  }
	  if (music.getStatus() != sf::SoundSource::Playing && musicc->playing) {
	    music.play();
	  }
	}
	catch (const graphic::AssetException &e) {
	  std::cerr << e.what() << std::endl;
	}
      }
    }
  }
}
