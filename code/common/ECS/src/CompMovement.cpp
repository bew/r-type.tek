
/**
 * @file CompMovement.hh
 * @author Alexis.
 * @brief Component implementing the movement for game entities.
 *
 */

#include "AComponent.hh"
#include "CompMovement.hh"

namespace ECS
{
  namespace Component
  {
    
    CompMovement::CompMovement(coordinates<int> coor, float speed, coordinates<float> dir) :
      AComponent(CLONABLE_MASK),
      _coo(coor),
      _dir(dir),
      _speed(speed),
      _advance(0.f, 0.f),
      _facingDir(CompMovement::FORWARD)
    {}
    
    CompMovement::~CompMovement()
    {}

    AComponent *CompMovement::clone(void) const {
      CompMovement *clone = new CompMovement();
      clone->_coo = _coo;
      clone->_dir = _dir;
      clone->_speed = _speed;
      clone->_advance = _advance;
      clone->_facingDir = _facingDir;
      return clone;
    }
    
    const std::string &CompMovement::getType() const
    {
      return Component::MOVEMENT;
    }
  }
}
