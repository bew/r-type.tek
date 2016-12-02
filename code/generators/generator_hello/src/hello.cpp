//
// Created by Pierre Rousselle on 18/11/2016.
//

#include <iostream>
#include "hello.hh"

const std::string &Libhello::getName(void) const {
  return _plugin_name;
};

Libhello::Libhello(void) :
  _plugin_name("hello module") {
};

EXPORT(Libhello);
