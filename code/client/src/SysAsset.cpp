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
      
      if (assetc && optionsc && assetc->store.getLocale() != optionsc->getLocale()) {
        assetc->store.empty();
	assetc->store.setLocale(optionsc->getLocale());
	assetc->store.loadAll();
      }
    }
  }
}
