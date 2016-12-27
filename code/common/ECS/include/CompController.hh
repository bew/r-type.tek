/**
 * @file CompController.hh
 * @author Nekhot.
 * @brief Component for entity that need too be controlled by external peripheric.
 */

#pragma once

#include "AComponent.hh"

namespace ECS {
  namespace Component {

    static const std::string CONTROLLER = "controller";

    /**
     * Component for controller
     */
    class CompController : public AComponent {
    public:
      
      /**
       * @return ECS::Cmponent::CONTROLLER
       */
      virtual const std::string &getType() const;

      /**
       * Booleans for controls
       */
      bool fire;
      bool up;
      bool down;
      bool right;
      bool left;

      virtual ~CompController(void);
    };
  }
}
