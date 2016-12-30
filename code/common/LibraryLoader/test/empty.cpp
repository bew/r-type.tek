//
// Created by Pierre Rousselle on 18/11/2016.
//

#include "empty.hh"

const std::string &Empty::getName(void) const {
  return _generator_name;
};

Empty::Empty(void) :
  _generator_name("Empty generator") {
};

void Empty::update(ECS::WorldData &world) {
}

EXPORT(Empty);
