
/**
 * @file SysMovement.cpp
 * @author Alexis.
 * @brief System updating the movement of entities.
 *
 */

#include "SysMovement.hh"
#include "CompMovement.hh"
#include "World.hh"


namespace ECS {
    namespace System {

        SysMovement::SysMovement()
        {}

        SysMovement::~SysMovement()
        {}

        void    SysMovement::computeNextCoordinates(Component::CompMovement *comp)
        {
            comp->_advance._x += comp->_dir._x * comp->_speed;
            comp->_advance._y += comp->_dir._y * comp->_speed;

            if (comp->_advance._x > 1.f || comp->_advance._x < -1.f) {
                comp->_coo._x += static_cast<int>(comp->_advance._x);
            }

            if (comp->_advance._y > 1.f || comp->_advance._y < -1.f) {
                comp->_coo._y += static_cast<int>(comp->_advance._y);
            }

            if (comp->_advance._x < 0.f)
                comp->_facingDir = Component::CompMovement::FacingDirection::BACKWARD;
            else
                comp->_facingDir = Component::CompMovement::FacingDirection::FORWARD;
            
            comp->_advance._y -= static_cast<int>(comp->_advance._y);
            comp->_advance._x -= static_cast<int>(comp->_advance._x);
        }

        void    SysMovement::update(WorldData &data)
        {
            for (auto &entity : data._gameEntities)
            {
                Component::CompMovement *comp = static_cast<Component::CompMovement *>(
                    entity->getComponent(Component::MOVEMENT));

                if (comp != nullptr)
                    this->computeNextCoordinates(comp);
            }
        }

    }
}