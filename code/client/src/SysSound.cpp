/**
 * @file SysSound.cpp
 * @author Nekhot
 * @brief Impelmentation of system procesing sound.
 */
#include <iostream>
#include "SysSound.hh"

namespace ECS {
  namespace System {

    void SysSound::update(WorldData &world) {
      Component::CompAsset *assetc = dynamic_cast<Component::CompAsset*>(world._systemEntity.getComponent(ECS::Component::STANDARD_ASSET));
      Component::CompOptions *optionsc = dynamic_cast<Component::CompOptions*>(world._systemEntity.getComponent(ECS::Component::OPTIONS));
      Component::CompSound *soundc;

      if (assetc && optionsc)
	for (ECS::Entity::Entity *entity : world._gameEntities) {
	  soundc = dynamic_cast<Component::CompSound*>(entity->getComponent(ECS::Component::SOUND));
	  if (soundc && !soundc->played) {
	    try {
	      soundc->sound.setBuffer(assetc->store.getSound(soundc->name).getLowLevelSound());
	      soundc->sound.setVolume(optionsc->getSoundEffectVolume());
	      logs::logger[logs::ASSET] << "play " << soundc->name << " at "<< optionsc->getSoundEffectVolume() << " for " << assetc->store.getSound(soundc->name).getLowLevelSound().getDuration().asSeconds()<< std::endl;
	      soundc->sound.play();
	      soundc->played = true;
	    }
	    catch (const graphic::AssetException &e) {
	      logs::logger[logs::ASSET] << e.what() << std::endl;
	    }
	  }
	}
    }
  }
}
