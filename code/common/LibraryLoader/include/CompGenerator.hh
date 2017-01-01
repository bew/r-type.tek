/**
 * @file CompGenerator.hh
 * @author Nekhot
 * @brief Component to hold a generator
 */

#pragma once

#include "ECS/AComponent.hh"
#include "libraryUtils.hh"
#include "Dependent_ptr.hpp"

namespace ECS {
  namespace Component {

    /**
     * The type of the generator component
     */
    static const std::string GENERATOR = "generator";

    /**
     * Component for generator
     */
    class CompGenerator : public AComponent {
    public:

      /**
       * Default ctor
       */
      CompGenerator();

      /**
       * The generator instance
       */
      Dependent_ptr<IGenerator, LibraryLoader> generator;      

      /**
       * @return ECS::Component::GENERATOR
       */
      virtual const std::string &getType() const;

      /**
       * Has the generator initialisation happen yet
       */
      bool loaded;
    };
  }
}
