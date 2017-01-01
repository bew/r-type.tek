/**
 * @file CompIA.hh
 * @author Nekhot
 * @brief Component to store the ia type
 */
#pragma once
#include "AComponent.hh"

namespace ECS {
  namespace Component {

    /**
     * The type of the asset component
     */
    static const std::string IA = "ia";

    /**
     * Component for ia
     */
    class CompIA : public AComponent {
    public:

      CompIA();
      /**
       * @param damage The damage
       */
      CompIA(const std::string &ia);

      /**
       * ia type
       */
      std::string name;

      /**
       * Tick at which ia begun to be processed, -1 if unknown
       */
      int born;

      /**
       * @return ECS::Component::IA
       */
      virtual const std::string &getType() const;

        /**
         * @return a document describing the component state
         */
        virtual bson::Document serialize() const;

        /**
         * @param document State to write into the component
         */
        virtual void deserialize(const bson::Document& document);

      /**
       * clone
       */
      AComponent *clone(void) const;
    };
  }
}
