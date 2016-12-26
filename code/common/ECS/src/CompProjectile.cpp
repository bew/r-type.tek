/**
 * @file CompProjectile.cpp
 * @author Nekhot.
 * @brief Implementation of Component for projectile.
 */

#include "CompProjectile.hh"

namespace ECS {
  namespace Component {

    CompProjectile::CompProjectile(const std::string &pname = "") :
      name(pname)
    {};

    const std::string &CompProjectile::getType() const {
      return Component::PROJECTILE;
    }
  }
}
