/**
 * @file CompMusic.cpp
 * @author Nekhot.
 * @brief Implementation of Component for musics. May diesapear.
 */

#include "../../common/ECS/include/CompSound.hh"

namespace ECS {
  namespace Component {

    CompSound::CompSound(const std::string &pname) :
      AComponent(CLONABLE_MASK),
      name(pname),
      played(false)
    {};
    
    const std::string &CompSound::getType() const {
      return Component::SOUND;
    }

    AComponent *CompSound::clone(void) const {
      return new CompSound(name);
    };
  }
}
