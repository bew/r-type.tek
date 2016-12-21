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
      Component::CompOptions *optionsc = dynamic_cast<Component::CompOptions*>(world._systemEntity.getComponent(ECS::Component::OPTIONS));

      if (musicc && assetc && assetc->store && optionsc) {
	try {
	  //bloaty and ugly. Still thinking about how to handle everyhing correctly.
	  if (optionsc->getMusicVolumeChanged() || musicc->getChanged()) {
	    assetc->store->getMusic(musicc->getMusic()).getLowLevelMusic().setVolume(optionsc->getMusicVolume());
	    optionsc->setMusicVolumeChanged(false);
	  }
	}
	catch (const graphic::AssetException &e) {
	  std::cerr << e.what() << std::endl;
	}
      }
    }
  }
}
