
/**
 * @file SysMovement.cpp
 * @author Alexis.
 * @brief System updating the movement of entities.
 *
 */

#include "SysMovement.hh"
#include "CompMovement.hh"
#include "CompCollideGrid.hh"
#include "CompHitbox.hh"
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

        void    SysMovement::putCoordinatesInGrid(Component::CompMovement *mov_comp,
                                                  Entity::Entity *entity,
                                                  Entity::Entity &sys_entity)
        {
            Component::CompCollideGrid *collision_comp = static_cast<Component::CompCollideGrid *>(
                sys_entity.getComponent(Component::COLLIDEGRID));
            Component::CompHitbox *hitbox_comp = static_cast<Component::CompHitbox *>(
                entity->getComponent(Component::HITBOX));
            if (collision_comp != nullptr && hitbox_comp != nullptr) {

                int x_base = (mov_comp->_coo._x - hitbox_comp->_midWidth) / GRID_NB_CASES;
                int x_final = (mov_comp->_coo._x + hitbox_comp->_midWidth) / GRID_NB_CASES;
                int y_base = (mov_comp->_coo._y - hitbox_comp->_midHeight) / GRID_NB_CASES;
                int y_final = (mov_comp->_coo._y + hitbox_comp->_midHeight) / GRID_NB_CASES;

                for (int i = y_base; i <= y_final; ++i) {
                    for (int j = x_base; j <= x_final; ++j) {
                        if (i >= 0 && i < GRID_NB_CASES && j >= 0 && j < GRID_NB_CASES)
                            collision_comp->addInGrid(j, i, entity);
                    }
                }
            }
        }
        
        void    SysMovement::update(WorldData &data)
        {
            for (auto &entity : data._gameEntities)
            {
                Component::CompMovement *comp = static_cast<Component::CompMovement *>(
                    entity->getComponent(Component::MOVEMENT));

                if (comp != nullptr) { 
                    this->computeNextCoordinates(comp);
                    this->putCoordinatesInGrid(comp, entity, data._systemEntity);
                }
            }
        }

        
    }
}
