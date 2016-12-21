/**
 * @file CompWindow.hh
 * @author Nekhot.
 * @brief Component for entity that need there own windows.
 */

#pragma once

#include "Graphic/MusicAsset.hh"
#include "ECS/AComponent.hh"

namespace ECS {
  namespace Component {

    static const std::string MUSIC = "music";

    /**
     * Component for music
     */
    class CompMusic : public AComponent {
    public:

      CompMusic(void);

      const std::string &getMusic(void) const;
      bool getChanged(void) const;
      void setMusic(const std::string &name);
      void setChanged(bool changed);
      
    protected:
      /**
       * The asset reference in assetStore
       */
      std::string _name;
      bool _changed;
    public:
      virtual const std::string &getType() const;
    };
  }
}
