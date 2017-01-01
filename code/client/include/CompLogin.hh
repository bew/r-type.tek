/**
 * @file CompLogin.hh
 * @author Nekhot
 * @brief Component for holding info about pre connection protocol.
 */

#pragma once

#include <string>
#include "ECS/AComponent.hh"

namespace ECS {
  namespace Component {

    /**
     * The type of the login component
     */
    static const std::string LOGIN = "login";

    /**
     * Component for holding system entity standard asset.
     */
    class CompLogin : public AComponent {
    public:

      CompLogin(void);

      std::string login;

      std::string password;
      
      /**
       * @return ECS::Component::STANDARD_ASSET
       */
      virtual const std::string &getType() const;
    };
  }
}
