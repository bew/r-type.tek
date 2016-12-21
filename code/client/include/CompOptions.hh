/**
 * @file CompOptions.hh
 * @author Nekhot.
 * @brief Header of Component for client option.
 */

#pragma once

#include <string>
#include "Graphic/AssetStore.hpp"
#include "ECS/AComponent.hh"

namespace ECS {
  namespace Component {

    static const std::string OPTIONS = "options";

    /**
     * Component for options
     */
    class CompOptions : public AComponent {
    public:

      CompOptions(void);

      /**
       * The locale to use for assets
       */
      std::string locale;

      /**
       * The music volume
       */
      float musicVolume;

      /**
       * Sound effect volume
       */
      float effectVolume;

      /**
       * @return ECS::Cmponent::OPTION
       */
      virtual const std::string &getType() const;

    };
  }
}
