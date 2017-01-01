/**
 * @file CompLogin.cpp
 * @author Nekhot
 * @brief Component for holding login.
 */

#include "CompLogin.hh"

namespace ECS {
  namespace Component {
    CompLogin::CompLogin(void) :
      login(""),
      password("")
    {};
    
    const std::string &CompLogin::getType() const {
      return Component::LOGIN;
    }
  }
}
