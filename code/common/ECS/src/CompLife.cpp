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
      if (currentLife > _currentLife) {
	_currentLife = currentLife;
	if (_currentLife > _maxLife)
	  _currentLife = _maxLife;
	return true;
      }
      else if (currentTick - lastDamageTick >= postDamageInvincibility || lastDamageTick == -1) {
	_currentLife = currentLife;
	if (_currentLife < 0)
	  _currentLife = 0;
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
