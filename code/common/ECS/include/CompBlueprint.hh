/**
 * @file CompBlueprint.hh
 * @author Nekhot
 * @brief Component for holding entity blueprint (for projectile and monster)
 */

#pragma once

#include <string>
#include <unordered_map>
#include "AComponent.hh"

namespace ECS {
  namespace Component {

    /**
     * The type of the asset component
     */
    static const std::string BLUEPRINT = "blueprint";

    /**
     * Component for holding system entity standard asset.
     */
    class CompBlueprint : public AComponent {
    public:

      /**
       * Store each blueprint by name
       */
      std::unordered_map<std::string, std::vector<ECS::AComponent *>> blueprints;

      /**
       * @return ECS::Component::BLUEPRINT
       */
      virtual const std::string &getType() const;
    };
  }
}
