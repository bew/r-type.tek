/**
 * @file CompController.hh
 * @author Nekhot.
 * @brief Component for entity that need too be controlled by external peripheric.
 */

#pragma once

#include "AComponent.hh"

namespace ECS {
  namespace Component {

    /**
     * Type identifier for CompController
     */
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

      /**
       * Is the fire button down
       */
      bool fire;

      /**
       * Is the up buttun down
       */
      bool up;

      /**
       * Is the down button down
       */
      bool down;

      /**
       * Is the right button down
       */
      bool right;
      
      /**
       * Is the left button down
       */
      bool left;

      /**
       * Default virtual destructor
       */
      virtual ~CompController(void);
    };
  }
}
