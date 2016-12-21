#pragma once

#include <string>
#include "ECS/AComponent.hh"
#include "ECS/Coordinates.hh"

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
       * Default constructor
       */
      CompSprite(void);
      
      /**
       * The name of the sprite, as reference to asset store.
       */
      std::string name;

      /**
       * Offset between the center of the sprite (height/2  ad width/2) and 2D coordinates of the entity 
       */
      coordinates<int> center;

      /**
       * @return ECS::Component::SPRITE
       */
      virtual const std::string &getType() const;
    };
  }
}
