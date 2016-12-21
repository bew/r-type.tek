/**
 * @file CompOptions.cpp
 * @author Nekhot.
 * @brief Implementation of Component for client options.
 */

#include "CompOptions.hh"

namespace ECS {
  namespace Component {

    CompOptions::CompOptions(void) :
      _locale(graphic::AssetStore::DEFAULT_LOCALE),
      _musicVolume(100),
      _effectVolume(100),
      _localeChanged(false),
      _effectVolumeChanged(false),
      _musicVolumeChanged(false)
    {};

    const std::string &CompOptions::getType() const {
      return Component::OPTIONS;
    }
    
    const std::string &CompOptions::getLocale(void) const {
      return _locale;
    };
    
    float CompOptions::getMusicVolume(void) const {
      return _musicVolume;
    };
    
    float CompOptions::getSoundEffectVolume(void) const {
      return _effectVolume;
    };
        
    void CompOptions::setLocale(const std::string &locale) {
      if (_locale != locale)
	_localeChanged = true;
      _locale = locale;
    };

    void CompOptions::setMusicVolume(float volume) {
      if (_effectVolume != volume)
	_effectVolumeChanged = true;
      _effectVolume = volume;
    };
    
    void CompOptions::setSoundEffectVolume(float volume) {
      if(_musicVolume != volume)
	_musicVolumeChanged = true;
      _musicVolume = volume;
    };
  }  
}
