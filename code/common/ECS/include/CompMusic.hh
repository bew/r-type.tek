/**
 * @file CompMusic.hh
 * @author Nekhot
 * @brief Component for the music of the system entity.
 */

#pragma once

#include "AComponent.hh"

namespace ECS {
  namespace Component {

    /**
     * The type of the asset component
     */
    static const std::string MUSIC = "music";

    /**
     * Component for music
     */
    class CompMusic : public AComponent {
    public:

      /**
       * @param name The name of the music
       */
      CompMusic(const std::string &name);

      /**
       * @return The music name
       */
      const std::string &getMusic(void) const;

      /**
       * @return if the music changed
       */
      bool getChanged(void) const;

      /**
       * @param name Name of the music This reference should be solvable in standard asset.
       */
      void setMusic(const std::string &name);
      /**
       * @param changed
       */
      void setChanged(bool changed);
      
    protected:
      
      /**
       * The asset reference in assetStore
       */
      std::string _name;

      /**
       * Tracker for modfication to music.
       */
      bool _changed;
    public:

      /**
       * @return ECS::Component::MUSIC
       */
      virtual const std::string &getType() const;
    };
  }
}
