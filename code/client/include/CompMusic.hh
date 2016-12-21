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

      /**
       * Is looping
       */
      bool loop;

      /**
       * Is playing (set)
       */
      bool playing;

      /**
       * The asset reference in assetStore
       */
      std::string name;
      
      virtual const std::string &getType() const;
    };
  }
}
