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
      _effectVolume(100)
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
    
    bool CompOptions::getEffectChanged(void) const {
      return _localeChanged;
    };
    
    bool CompOptions::getVolumeChanged(void) const {
      return _effectVolumeChanged;
    };
    
    bool CompOptions::getLocaleChanged(void) const {
      return _musicVolumeChanged;
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
    
    void CompOptions::setLocaleChanged(bool changed) {
      _localeChanged = changed;
    };
    void CompOptions::setMusicChanged(bool changed) {
      _effectVolumeChanged = changed;
    };
    void CompOptions::setEffectChanged(bool changed) {
      _musicVolumeChanged = changed;
    };

  }  
}
