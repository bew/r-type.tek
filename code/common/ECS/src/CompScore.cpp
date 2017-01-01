/**
 * @file CompScore.cpp
 * @author Nekhot.
 * @brief Implementation of score component.
 */

#include "CompScore.hh"

namespace ECS {
  namespace Component {
    CompScore::CompScore(int pscore) :
      AComponent(CLONABLE_MASK),
      score(pscore)
    {}

    const std::string &CompScore::getType() const {
      return Component::SCORE;
    }

    AComponent *CompScore::clone(void) const {
      return new CompScore(score);
    }

      bson::Document  CompScore::serialize() const {
          bson::Document doc;
          doc << u8"score" << score;
          return doc;
      };

      void  CompScore::deserialize(const bson::Document& document) {
          document[u8"score"] >> score;
      }

  }
}
