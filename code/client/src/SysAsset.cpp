/**
 * @file SysAsset.cpp
 * @author Nekhot
 * @brief Impelmentation of system procesing asset.
 */

#include "SysAsset.hh"

namespace ECS {
  namespace System {

    void SysAsset::update(WorldData &world) {
      
      Component::CompAsset *assetc = dynamic_cast<Component::CompAsset*>(world._systemEntity.getComponent(ECS::Component::STANDARD_ASSET));
      Component::CompOptions *optionsc = dynamic_cast<Component::CompOptions*>(world._systemEntity.getComponent(ECS::Component::OPTIONS));
      
      if (assetc && optionsc) {
	if (assetc->store.getLocale() != optionsc->getLocale()) {
	  assetc->store.empty();
	  assetc->loaded = false;
	}
	if (!assetc->loaded) {
	  assetc->store.setLocale(optionsc->getLocale());
	  assetc->store.loadAll();
	  assetc->loaded = true;
	}
      }
    }  
  }
}
