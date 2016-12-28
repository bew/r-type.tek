/**
 * @file CompProjectile.cpp
 * @author Nekhot.
 * @brief Implementation of Component for projectile.
 */

#include "CompProjectile.hh"

namespace ECS {
  namespace Component {

    CompProjectile::CompProjectile(const std::string &pname) :
      name(pname),
      fireRate(12),
      lastFireTick(-12)
    {};

    const std::string &CompProjectile::getType() const {
      return Component::PROJECTILE;
    }
  }
}
