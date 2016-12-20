/**
 * @file SysWindow.cpp
 * @author Nekhot.
 * @brief Impelmentation of system procesing windows.
 */

#include "SysAsset.hh"

namespace ECS {
  namespace System {

    void SysAsset::update(WorldData &world) {
      
      Component::CompAsset *assetc = dynamic_cast<Component::CompAsset*>(world._systemEntity.getComponent(ECS::Component::STANDARD_ASSET));
      Component::CompOptions *optionsc = dynamic_cast<Component::CompOptions*>(world._systemEntity.getComponent(ECS::Component::OPTIONS));
      
      if (assetc && optionsc) {
        if (assetc->store && assetc->store->getLocale != optionsc->locale) {
	  delete assetc->store;
	  assetc->store = nullptr;
	}
	if (!assetc->store) {
	  assetc->store = new graphic::GroupedAssetStore("asset", "standard", optionsc->locale);
	  assetc->store->loadAll();
	}
      }
    }
  }
}
