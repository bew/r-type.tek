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

    public:
      /**
       * @return ECS::Cmponent::OPTION
       */
      virtual const std::string &getType() const;

    };
  }
}
