/**
 * @file SysWindow.cpp
 * @author Nekhot.
 * @brief Impelmentation of system procesing windows.
 */

#include "SysMusic.hh"

namespace ECS {
  namespace System {

    void SysMusic::update(WorldData &world) {
      Component::CompMusic *musicc = dynamic_cast<Component::CompMusic*>(entity.getComponent(ECS::Component::MUSIC));
      Component::CompAsset *assetc = dynamic_cast<Component::CompAsset*>(entity.getComponent(ECS::Component::STANDARD_ASSET));
      if (musicc && musicc->name != "" && assetc && assetc->store) {
	try {
	  sf::Asset &music = assetc->store->getMusic(musicc->name);
	  if (music.getStatus == sf::SoundSource::Playing && !music->playing) {
	    music.stop();
	  }
	  if (!music.getStatus == sf::SoundSource::Playing && music->playing) {
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
