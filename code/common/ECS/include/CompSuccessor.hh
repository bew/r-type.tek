/**
 * @file CompSuccessor.hh
 * @author Nekhot
 * @brief Component to set a successor to spawn at the death of entity
 */

#pragma once

#include "AComponent.hh"

namespace ECS {
  namespace Component {

    /**
     * The type of the asset component
     */
    static const std::string SUCCESSOR = "successor";

    /**
     * Component for successor
     */
    class CompSuccessor : public AComponent {
    public:

      CompSuccessor(void) = delete;
      
      /**
       * @param successor The successor
       */
      CompSuccessor(const std::string &successor);

      /**
       * The successor
       */
      std::string _successor;

        /**
         * @return A pointer to a new CompSprite with a state similar to this
         */
        virtual AComponent *clone(void) const;

        /**
         * @return a document describing the component state
         */
        virtual bson::Document serialize() const;

        /**
         * @param document State to write into the component
         */
        virtual void deserialize(const bson::Document& document);

      /**
       * @return ECS::Component::SUCCESSOR
       */
      virtual const std::string &getType() const;
    };
  }
}
