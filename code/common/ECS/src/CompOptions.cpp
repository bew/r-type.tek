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
      _musicVolumeChanged(false),
      _fullscreen(false),
      _width(1280),
      _height(720),
      _aaliasing(0),
      _title("Aru Taipu"),
      _windowChanged(false)
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
    
    bool CompOptions::getFullscreen(void) const {
      return _fullscreen;
    };

    unsigned int CompOptions::getHeight(void) const {
      return _height;
    };

    unsigned int CompOptions::getWidth(void) const {
      return _width;
    };

    unsigned int CompOptions::getAAliasing(void) const {
      return _aaliasing;
    };
    
    const std::string &CompOptions::getTitle(void) const {
      return _title;
    };
    
    void CompOptions::setFullscreen(bool fullscreen) {
      if (_fullscreen != fullscreen)
        _windowChanged = true;
      _fullscreen = fullscreen;
    };

    void CompOptions::setHeight(unsigned int height) {
      if (_height != height)
	_windowChanged = true;
      _height = height;
    };
    
    void CompOptions::setWidth(unsigned int width) {
      if (_width != width)
	_windowChanged = true;
      _width = width;
    };

    void CompOptions::setAAliasing(unsigned int aaliasing) {
      if (_aaliasing != aaliasing)
	_windowChanged = true;
      _aaliasing = aaliasing;
    };

    void CompOptions::setTitle(const std::string &title) {
      if (_title != title)
	_windowChanged = true;
      _title = title;
    };
  }
}
