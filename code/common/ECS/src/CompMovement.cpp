
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
      AComponent(CLONABLE_MASK  | SERVER_SERIALIZABLE_MASK),
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

    

    bson::Document CompMovement::serialize() const {
      bson::Document doc;
      doc << "coo_x" << _coo._x;
      doc << "coo_y" << _coo._y;
      doc << "dir_x" << _dir._x;
      doc << "dir_y" << _dir._y;
      doc << "speed" << _speed;
      doc << "advance_x" << _advance._x;
      doc << "advance_y" << _advance._y;
      doc << "face" << _facingDir;
      return doc;
    };

    void  CompMovement::deserialize(const bson::Document& document) {
      double dx, dy;
      double speed;
      double ax, ay;
      int facing;
      
      document["coo_x"] >> _coo._x;
      document["coo_y"] >> _coo._y;
      document["dir_x"] >> dx; _dir._x = dx;
      document["dir_y"] >> dy; _dir._y = dy;
      document["speed"] >> speed; _speed = speed;
      document["advance_x"] >> ax; _advance._x = ax;
      document["advance_y"] >> ay; _advance._y = ay;
      document["face"] >> facing; _facingDir = static_cast<CompMovement::FacingDirection>(facing);
    }

  }
}
