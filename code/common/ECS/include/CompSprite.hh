/**
 * @file CompSprite.cpp
 * @author Nekhot
 * @brief Component for holding sprites.
 */

#pragma once

#include <string>
#include "AComponent.hh"
#include "Coordinates.hh"

namespace ECS {
  namespace Component {

    /**
     * Component type
     */
    static const std::string SPRITE = "sprite";

    /**
     * Component for Sprites
     */
    class CompSprite : public AComponent {
    public:

      /**
       * Value to signal that the sprite is currently unset
       */
      static const std::string NO_SPRITE;

      /**
       * Value to signal that the sprite is not anmated
       */
      static const std::string NO_ANIMATION;
      
      /**
       * Constructor
       *
       * @param pname Name of sprite, default to CompSprite::NO_SPRITE
       * @param x X center offset of the sprite Default to 0
       * @param y Y center offset of the sprite Defautl to 0
       * @param animated Default to false.
       * @param scale The scale of the sprite
       */
      CompSprite(const std::string &pname = "", coordinates<int> coor = {0, 0}, const std::string &animated = NO_ANIMATION, const coordinates<float> &pscale = {1.0, 1.0});
      
      /**
       * The name of the sprite, as reference to asset store.
       */
      std::string name;

      /**
       * Offset between the center of the sprite (height/2  ad width/2) and 2D coordinates of the entity 
       */
      coordinates<int> center;

      /**
       * Is the sprite an animated sprites
       */
      std::string animation;

      /**
       * The tick at which animation cycle begun. -1 If unknown
       */
      int animationTick;
      
      /**
       * The scale of the sprite
       */
      coordinates<float> scale;

      /**
       * @return A pointer to a new CompSprite with a state similar to this
       */
      virtual AComponent *clone(void) const;

      /**
       * @return ECS::Component::SPRITE
       */
      virtual const std::string &getType() const;
    };
  }
}
