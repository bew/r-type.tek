/**
 * @file CompLife.cpp
 * @author Tookie
 * @brief Component implementing the life for game entities.
 *
 */

#include "CompLife.hh"

namespace ECS
{
  namespace Component
  {
    
    CompLife::CompLife(unsigned int maxLife, int ppostDamageInvincibility) :
      AComponent(),
      _maxLife(maxLife),
      _currentLife(maxLife),
      postDamageInvincibility(ppostDamageInvincibility),
      lastDamageTick(-1)
    {}
    
    CompLife::~CompLife()
    {}

    int CompLife::getCurrentLife(void) const {
      return _currentLife;
    }

    bool CompLife::setCurrentLife(int currentLife, int currentTick) {
      if (currentTick - lastDamageTick >= postDamageInvincibility || lastDamageTick == -1) {
	_currentLife = currentLife;
	lastDamageTick = currentTick;
	return true;
      }
      return false;
    }
      
    const std::string &CompLife::getType() const {
      return Component::LIFE;
    }
    
    AComponent *CompLife::clone(void) const {
      return new CompLife(_maxLife, postDamageInvincibility);
    }
  }
}
