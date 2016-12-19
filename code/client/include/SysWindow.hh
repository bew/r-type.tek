#pragma once

#include "ECS/World.hh"
#include "ECS/Entity.hh"
#include "ECS/ISystem.hh"
#include "CompWindow.hh"

namespace ECS {
  namespace System {
    class SysWindow : public ISystem {
      virtual void update(ECS::WorldData &);
      void update(ECS::Entity::Entity &);
    };
  }
}
