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

    static const std::string OPTIONS = "options";

    /**
     * Component for options
     */
    class CompOptions : public AComponent {
    public:

      CompOptions(void);

      const std::string &getLocale(void) const;
      float getMusicVolume(void) const;
      float getSoundEffectVolume(void) const;
      bool getEffectChanged(void) const;
      bool getVolumeChanged(void) const;
      bool getLocaleChanged(void) const;
      
      void setLocale(const std::string &);
      void setMusicVolume(float);
      void setSoundEffectVolume(float);
      void setLocaleChanged(bool);
      void setMusicChanged(bool);
      void setEffectChanged(bool);
      
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
