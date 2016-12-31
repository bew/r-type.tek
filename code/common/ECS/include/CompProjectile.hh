/**
 * @file CompProjectile.hh
 * @author Nekhot
 * @brief Component for holding projectile that are launcheable.
 */

#pragma once

#include <string>
#include "Coordinates.hh"
#include "AComponent.hh"

namespace ECS {
  namespace Component {

    /**
     * The type of the asset component
     */
    static const std::string PROJECTILE = "projectile";

    /**
     * Component for holding system entity standard asset.
     */
    class CompProjectile : public AComponent {
    public:

      /**
       * Constructor
       *
       * @param name The name of the projectile bluprint
       */
      CompProjectile(const std::string &pname);

      /**
       * Name of the projectile entity blueprint
       */
      std::string name;

      /**
       * Rate of fire in tick
       */
      int fireRate;

      /**
       * Last tick at which projectile was fired
       */
      unsigned int lastFireTick;

      /**
       * @return ECS::Component::PROJECTILE
       */
      virtual const std::string &getType() const;
    };
  }
}
