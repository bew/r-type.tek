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
       * @return Getter
       */
      bool getEffectVolumeChanged(void) const;

      /**
       * @return Getter
       */
      bool getMusicVolumeChanged(void) const;

      /**
       * @return Getter
       */
      bool getLocaleChanged(void) const;

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
       * @param ... Setter
       */
      void setLocaleChanged(bool);

      
      /**
       * @param ... Setter
       */
      void setMusicVolumeChanged(bool);
      
      /**
       * @param ... Setter
       */
      void setEffectVolumeChanged(bool);
      
    protected:
      /**
       * The locale to use for assets
       */
      std::string _locale;
      bool _localeChanged;

      /**
       * The music volume
       */
      float _musicVolume;
      bool _musicVolumeChanged;

      /**
       * Sound effect volume
       */
      float _effectVolume;
      bool _effectVolumeChanged;

    public:
      /**
       * @return ECS::Cmponent::OPTION
       */
      virtual const std::string &getType() const;

    };
  }
}
