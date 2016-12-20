/**
 * @file CompOptions.hh
 * @author Nekhot.
 * @brief Header of Component for client option.
 */

#pragma once

#include <string>
#include "Graphic/AssetStore.hh"
#include "ECS/AComponent.hh"

namespace ECS {
  namespace Component {

    static const std::string OPTIONS = "options";

    /**
     * Component for options
     */
    class CompOptions : public AComponent {
    public:

      /**
       * The locale to use for assets
       */
      std::string locale;
    };
  }
}
