/**
 * @file CompSound.hh
 * @author Nekhot
 * @brief Component for the sounds.
 */

#pragma once

#include "AComponent.hh"

namespace ECS {
  namespace Component {

    /**
     * The type of the asset component
     */
    static const std::string SOUND = "sound";

    /**
     * Component for music
     */
    class CompSound : public AComponent {
    public:

      /**
       * @param Sound The name of the sound to play
       */
      CompSound(const std::string &sound);

      /**
       * Name of the sound
       */
      std::string name;

      /**
       * has the sound be played (should be repaced by removing the component ?)
       */
      bool played;

      /**
       * @return A pointer to a new CompSound with a state similar to this
       */
      virtual AComponent *clone(void) const;
  
    public:

      /**
       * @return ECS::Component::SOUND
       */
      virtual const std::string &getType() const;
    };
  }
}
