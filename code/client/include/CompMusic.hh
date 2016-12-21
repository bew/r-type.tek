/**
 * @file CompWindow.hh
 * @author Nekhot.
 * @brief Component for entity that need there own windows.
 */

#pragma once

#include "ECS/AComponent.hh"

namespace ECS {
  namespace Component {

    /**
     * Component type
     */
    static const std::string MUSIC = "music";

    /**
     * Component for music
     */
    class CompMusic : public AComponent {
    public:

      CompMusic(void);

      /**
       * @return The music name
       */
      const std::string &getMusic(void) const;

      /**
       * @return if the music changed
       */
      bool getChanged(void) const;

      /**
       * @param name Name of the music
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
      bool _changed;
    public:
      virtual const std::string &getType() const;
    };
  }
}
