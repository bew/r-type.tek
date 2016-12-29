/**
 * @file CompDamage.hh
 * @author Nekhot
 * @brief Component to store amount of damage an entity can do
 */
#pragma once

#include "AComponent.hh"

namespace ECS {
  namespace Component {

    /**
     * The type of the asset component
     */
    static const std::string DAMAGE = "damage";

    /**
     * Component for death
     */
    class CompDamage : public AComponent {
    public:

      CompDamage(void) = delete;

      /**
       * @param damage The damage
       */
      CompDamage(int damage);

      /**
       * amount of damage
       */
      int damage;
      
      /**
       * @return ECS::Component::DAMAGE
       */
      virtual const std::string &getType() const;

      /**
       * clone
       */
      AComponent *clone(void) const;
    };
  }
}
