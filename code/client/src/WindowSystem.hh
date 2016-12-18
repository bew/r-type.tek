#pragma once

#include "alpha.hpp"
#include "WindowComponent.hh"

class WindowSystem : public System {
  virtual void process(Entity &);
};
