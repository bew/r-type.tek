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
       * @return ECS::Component::DEATH
       */
      virtual const std::string &getType() const;
    };
  }
}
