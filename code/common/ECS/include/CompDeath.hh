/**
 * @file CompDeath.hh
 * @author Nekhot
 * @brief Component to signal an entity as dead
 */

#pragma once

#include "AComponent.hh"

namespace ECS {
  namespace Component {

    /**
     * The type of the asset component
     */
    static const std::string DEATH = "death";

    /**
     * Component for death
     */
    class CompDeath : public AComponent {
    public:
      
      /**
       * @param delay Delay in tick before deletion
       * @param successor The successor
       */
      CompDeath(int delay = 0);

      /**
       * Delay before deleting the entity
       */
      int _delay;

      /**
       * @return A pointer to a new CompDeath with a state similar to this
       */
      virtual AComponent *clone(void) const;

      
      /**
       * @return ECS::Component::DEATH
       */
      virtual const std::string &getType() const;
    };
  }
}
