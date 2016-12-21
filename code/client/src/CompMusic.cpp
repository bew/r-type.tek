/**
 * @file CompWindow.cpp
 * @author Nekhot.
 * @brief Implementation of Component for entity that need there own windows.
 */

#include "CompMusic.hh"

namespace ECS {
  namespace Component {

    CompMusic::CompMusic(void) :
      loop(false),
      playing(false),
      name("")
    {};

    const std::string &CompMusic::getType() const
    {
      return Component::MUSIC;
    }
  }
}
