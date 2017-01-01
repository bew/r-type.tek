/**
 * @file CompController.cpp
 * @author Nekhot.
 * @brief Implementation of Component for client control.
 */

#include "CompController.hh"

namespace ECS {
  namespace Component {
    CompController::CompController(void) :
      AComponent(CLIENT_SERIALIZABLE_MASK) {
    };
    
    const std::string &CompController::getType() const {
      return Component::CONTROLLER;
    };

    bson::Document  CompController::serialize() const {
      bson::Document doc;
      doc << "up" << up;
      doc << "down" << down;
      doc << "left" << left;
      doc << "right" << right;
      doc << "fire" << fire;
      return doc;
    };

    void  CompController::deserialize(const bson::Document& document) {
      document["fire"] >> fire;
      document["left"] >> left;
      document["right"] >> right;
      document["up"] >> up;
      document["down"] >> down;
    }

    CompController::~CompController(void) {};
  }
}
