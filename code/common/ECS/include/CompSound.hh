/**
 * @file CompSound.hh
 * @author Nekhot
 * @brief Component for the sounds.
 */

#pragma once

#include "AComponent.hh"
// See sound member
#include "SFML/Audio/Sound.hpp"

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
       * The sfml sound.
       * For tesing, once geenrator are not loaeded client side anymore, this should be removed.
       * This only work as a placeholder.
       */
      sf::Sound sound;


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
