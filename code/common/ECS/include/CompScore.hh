/**
 * @file CompScore.hh
 * @author Nekhot
 * @brief Component to store score
 */

#pragma once

#include "AComponent.hh"

namespace ECS {
  namespace Component {

    /**
     * The type of the score component
     */
    static const std::string SCORE = "score";

    /**
     * Component for score
     */
    class CompScore : public AComponent {
    public:

      /**
       * @param score The initial stored score 
       */
      CompScore(int score = 0);

      /**
       * The stored score
       */
      int score;

      /**
       * @return A pointer to a new CompScore with a state similar to this
       */
      virtual AComponent *clone(void) const;


      /**
       * @return ECS::Component::SCORE
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
    };
  }
}
