/**
 * @file SysGenerator.cpp
 * @author Nekhot
 * @brief Implementation of system running generators.
 */
#include "SysGenerator.hh"

namespace ECS {
  namespace System {
    void SysGenerator::update(WorldData &world) {
      Component::CompGenerator *generatorc = dynamic_cast<Component::CompGenerator *>(world._systemEntity.getComponent(Component::GENERATOR));

      if (generatorc && generatorc->generator)
	generatorc->generator->update(world);
    }
  }
}
