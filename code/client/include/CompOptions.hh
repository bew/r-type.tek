/**
 * @file CompOptions.hh
 * @author Nekhot.
 * @brief Header of Component for client option.
 */

#pragma once

#include <string>
#include "Graphic/AssetStore.hpp"
#include "ECS/AComponent.hh"

namespace ECS {
  namespace Component {

    /**
     * Type for options component
     */
    static const std::string OPTIONS = "options";

    /**
     * Component for options
     */
    class CompOptions : public AComponent {
    public:

      CompOptions(void);

      /**
       * @return Getter
       */
      const std::string &getLocale(void) const;

      /**
       * @return Getter
       */
      float getMusicVolume(void) const;

      /**
       * @return Getter
       */
      float getSoundEffectVolume(void) const;

      /**
       * @param ... Setter Will also set according 'changed' to true
       */
      void setLocale(const std::string &);

      
      /**
       * @param ... Setter Will also set according 'changed' to true
       */
      void setMusicVolume(float);

      
      /**
       * @param ... Setter Will also set according 'changed' to true
       */
      void setSoundEffectVolume(float);

      
      /**
       * @return Getter
       */
      bool getFullscreen(void) const;

      /**
       * @return Getter
       */
      unsigned int getHeight(void) const;

      /**
       * @return Getter
       */
      unsigned int getWidth(void) const;

      /**
       * @return Getter
       */
      const std::string &getTitle(void) const;

      /**
       * @return Getter
       */
      unsigned int getAAliasing(void) const;

      /**
       * @param ... Setter, will also set changed to true
       */
      void setFullscreen(bool);

      /**
       * @param ... Setter, will also set changed to true
       */
      void setHeight(unsigned int);

      /**
       * @param ... Setter, will also set changed to true
       */
      void setWidth(unsigned int);

      /**
       * @param ... Setter, will also set changed to true
       */
      void setAAliasing(unsigned int);

      /**
       * @param ... Setter, will also set changed to true
       */
      void setTitle(const std::string &);


      /**
       * True to fire locale_changed event
       */
      bool _localeChanged;
      /**
       * True to fire music_config_changed
       */
      bool _musicVolumeChanged;

      /**
       * True to fire effect_config_changed
       */
      bool _effectVolumeChanged;

      /**
       * True to fire window_config_changed
       */
      bool _windowChanged;

      /**
       * Has the configuration been loaded
       */
      bool loaded;
      
    protected:
      /**
       * The locale to use for assets
       */
      std::string _locale;

      /**
       * The music volume
       */
      float _musicVolume;

      /**
       * Sound effect volume
       */
      float _effectVolume;

      /**
       * Is the window fullscreen
       */
      bool _fullscreen;
  
      /**
       * Window width in px
       */
      unsigned int _width;
  
      /**
       * Window height in px
       */
      unsigned int _height;
  
      /**
       * anti aliasing level
       */
      unsigned int _aaliasing;
  
      /**
       * Default name for the windows
       */
      std::string _title;

    public:
      /**
       * The server url
       */
      std::string _serverUrl;

      /**
       * The server port
       */
      short _serverPort;

      /**
       * @return ECS::Cmponent::OPTION
       */
      virtual const std::string &getType() const;

    };
  }
}
