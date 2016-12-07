//
// Created by Pierre Rousselle on 18/11/2016.
//

#include <iostream>
#include "empty.hh"

const std::string &Empty::getName(void) const {
  return _generator_name;
};

Empty::Empty(void) :
  _generator_name("Empty generator") {
};

std::vector<Entity> Empty::process(std::vector<Entity> &e, EngineStatus &s) {
  return std::vector<Entity>();
};


EXPORT(Empty);
