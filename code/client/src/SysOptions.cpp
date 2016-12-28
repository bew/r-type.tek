/**
 * @file SysAsset.cpp
 * @author Nekhot
 * @brief Impelmentation of system procesing options.
 */
#include "SysOptions.hh"

namespace ECS {
  namespace System {

    void SysOptions::update(WorldData &world) {

      Component::CompEvent *eventc = dynamic_cast<Component::CompEvent*>(world._systemEntity.getComponent(ECS::Component::EVENT));
      Component::CompOptions *optionsc = dynamic_cast<Component::CompOptions*>(world._systemEntity.getComponent(ECS::Component::OPTIONS));
      
      if (eventc && optionsc) {
	if (!optionsc->loaded) {
	  SysOptions::READ_CONFIG_FILE<false>(nullptr, world);
	  optionsc->loaded = true;
	  eventc->addHook("config_update", SysOptions::WRITE_CONFIG_FILE<true>);
	}
	if (optionsc->_localeChanged || optionsc->_effectVolumeChanged || optionsc->_musicVolumeChanged || optionsc->_windowChanged) {
          eventc->addEvent("config_update", nullptr);
        }
	if (optionsc->_localeChanged) {
	  eventc->addEvent("config_update_locale", nullptr);
	  optionsc->_localeChanged = false;
	}
	if (optionsc->_effectVolumeChanged) {
          eventc->addEvent("config_update_effect", nullptr);
          optionsc->_effectVolumeChanged = false;
        }
	if (optionsc->_musicVolumeChanged) {
          eventc->addEvent("config_update_music", nullptr);
          optionsc->_musicVolumeChanged = false;
        }
	if (optionsc->_windowChanged) {
          eventc->addEvent("config_update_window", nullptr);
          optionsc->_windowChanged = false;
        }
      }
    }

    const std::string SysOptions::CONFIG_FILE = "configuration.json";
  }
}
