/**
 * @file CompMusic.cpp
 * @author Nekhot.
 * @brief Implementation of Component for musics. May diesapear.
 */

#include "CompMusic.hh"

namespace ECS {
  namespace Component {

    CompMusic::CompMusic(const std::string &name) :
      _name(name)
    {};

    const std::string &CompMusic::getMusic(void) const {
      return _name; 
    };
    bool CompMusic::getChanged(void) const {
      return _changed;
    };
    void CompMusic::setMusic(const std::string &name) {
      if (name != _name)
	_changed = true;
      _name = name;
    };
    void CompMusic::setChanged(bool changed) {
      _changed = changed;
    };
    
    const std::string &CompMusic::getType() const {
      return Component::MUSIC;
    }
  }
}
