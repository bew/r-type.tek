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

      static const std::string NO_SPRITE;
      
      /**
       * Constructor
       *
       * @param pname Name of sprite, default to CompSprite::NO_SPRITE
       * @param x X center offset of the sprite Default to 0
       * @param y Y center offset of the sprite Defautl to 0
       */
      CompSprite(const std::string &pname = "", int x = 0, int y = 0);
      
      /**
       * The name of the sprite, as reference to asset store.
       */
      std::string name;

      /**
       * Offset between the center of the sprite (height/2  ad width/2) and 2D coordinates of the entity 
       */
      coordinates<int> center;

      virtual AComponent *clone(void) const;

      /**
       * @return ECS::Component::SPRITE
       */
      virtual const std::string &getType() const;
    };
  }
}
