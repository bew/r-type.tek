/**
 * @file SysAssets.hh
 * @author Nekhot.
 * @brief Header of System for loading standard asset.
 */

#pragma once

#include "World.hh"
#include "Entity.hh"
#include "ISystem.hh"
#include "CompEvent.hh"
#include "CompAsset.hh"
#include "CompOptions.hh"

namespace ECS {
  namespace System {

    /**
     * System for window
     */
    class SysAsset : public ISystem {
    public:
      
      /**
       * Update method
       *
       * @param world All the data about the world
       */
      virtual void update(ECS::WorldData &world);

      /**
       * Handler for Reloading the asset store
       */
      template<bool repeat>
      static bool RELOAD_ASSET(ECS::Component::CompEvent::IEvent *event, ECS::WorldData &world) {
	
	Component::CompAsset *assetc = dynamic_cast<Component::CompAsset*>(world._systemEntity.getComponent(ECS::Component::STANDARD_ASSET));
	Component::CompOptions *optionsc = dynamic_cast<Component::CompOptions*>(world._systemEntity.getComponent(ECS::Component::OPTIONS));
	
	if (assetc && optionsc && assetc->store.getLocale() != optionsc->getLocale()) {
	  assetc->store.empty();
	  assetc->store.setLocale(optionsc->getLocale());
	  assetc->store.loadAll();
	}
	return repeat;
      }
      
    };
  }
}
