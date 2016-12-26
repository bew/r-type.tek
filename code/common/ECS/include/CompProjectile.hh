/**
 * @file CompProjectile.hh
 * @author Nekhot
 * @brief Component for holding projectile that are launcheable.
 */

#pragma once

#include <string>
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
       * Construcotr
       *
       * @param name The name of the projectile bluprint, default to ""
       */
      CompProjectile(const std::string &pname = "");

      /**
       * Name of the projectile entity blueprint
       */
      std::string name;

      /**
       * @return ECS::Component::PROJECTILE
       */
      virtual const std::string &getType() const;
    };
  }
}
