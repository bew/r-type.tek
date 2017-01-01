/**
 * @file CompSueccesor.cpp
 * @author Nekhot.
 * @brief Implementation of Component to hold a sucessor.
 */

#include "CompSuccessor.hh"

namespace ECS {
  namespace Component {
    CompSuccessor::CompSuccessor(const std::string &successor) :
      _successor(successor)
    {}

    const std::string &CompSuccessor::getType() const {
      return Component::SUCCESSOR;
    }

    AComponent *CompSuccessor::clone(void) const {
      return new CompSuccessor(_successor);
    }

      bson::Document CompSuccessor::serialize() const {
          bson::Document doc;
          doc << u8"successor" << _successor;
          return doc;
      };

      void  CompSuccessor::deserialize(const bson::Document& document) {
          document[u8"successor"] >> _successor;
      }

  }
}
