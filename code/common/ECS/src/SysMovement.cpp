
/**
 * @file SysMovement.cpp
 * @author Alexis.
 * @brief System updating the movement of entities.
 *
 */

#include "SysMovement.hh"
#include "CompMovement.hh"
#include "CompCollision.hh"
#include "CompHitbox.hh"
#include "CompType.hh"
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

            if (comp->_advance._x >= 1.f || comp->_advance._x <= -1.f) {
                comp->_coo._x += static_cast<int>(comp->_advance._x);
            }

            if (comp->_advance._y >= 1.f || comp->_advance._y <= -1.f) {
                comp->_coo._y += static_cast<int>(comp->_advance._y);
            }

            if (comp->_advance._x < 0.f)
                comp->_facingDir = Component::CompMovement::FacingDirection::BACKWARD;
            else
                comp->_facingDir = Component::CompMovement::FacingDirection::FORWARD;

            comp->_advance._y -= static_cast<int>(comp->_advance._y);
            comp->_advance._x -= static_cast<int>(comp->_advance._x);		      
	}

        void    SysMovement::putEntityInGrid(Component::CompMovement *mov_comp,
                                             Entity::Entity *entity,
                                             Entity::Entity &sys_entity)
        {
            Component::CompCollision *collision_comp = static_cast<Component::CompCollision *>(
                sys_entity.getComponent(Component::COLLISION));
            Component::CompHitbox *hitbox_comp = static_cast<Component::CompHitbox *>(
                entity->getComponent(Component::HITBOX));
            if (collision_comp != nullptr && hitbox_comp != nullptr) {

                unsigned      cell_width = Component::XMAX / GRID_NB_CASES;
                unsigned      cell_height = Component::YMAX / GRID_NB_CASES;
                
                int x_base = (mov_comp->_coo._x - hitbox_comp->_midWidth) / cell_width;
                int x_final = (mov_comp->_coo._x + hitbox_comp->_midWidth) / cell_width;
                int y_base = (mov_comp->_coo._y - hitbox_comp->_midHeight) / cell_height;
                int y_final = (mov_comp->_coo._y + hitbox_comp->_midHeight) / cell_height;

                for (int y = y_base; y <= y_final; ++y) {
                    for (int x = x_base; x <= x_final; ++x) {
                        if (y >= 0 && y < GRID_NB_CASES && x >= 0 && x < GRID_NB_CASES)
                            collision_comp->addInGrid(x, y, entity);
                    }
                }
            }
        }
        
        void    SysMovement::playerCheckPosition(const Entity::Entity &entity)
        {
            Component::CompType *type_comp = static_cast<Component::CompType *>(
                entity.getComponent(Component::TYPE));

            if (type_comp != nullptr && type_comp->_type == Component::CompType::Type::PLAYER)
            {
                Component::CompHitbox *hitbox_comp = static_cast<Component::CompHitbox *>(
                    entity.getComponent(Component::HITBOX));
                Component::CompMovement *move_comp = static_cast<Component::CompMovement *>(
                    entity.getComponent(Component::MOVEMENT));

                if (!hitbox_comp || !move_comp)
                    return;
                
                int y_top_diff = move_comp->_coo._y - hitbox_comp->_midHeight;
                int y_bottom_diff = move_comp->_coo._y + hitbox_comp->_midHeight;
                int x_left_diff = move_comp->_coo._x - hitbox_comp->_midWidth;
                int x_right_diff = move_comp->_coo._x + hitbox_comp->_midWidth;
                
                if (y_top_diff < 0)
                    move_comp->_coo._y += -y_top_diff;
                if (y_bottom_diff > Component::YMAX)
                    move_comp->_coo._y -= y_bottom_diff - Component::YMAX;
                if (x_left_diff < 0)
                    move_comp->_coo._x += -x_left_diff;
                if (x_right_diff > Component::XMAX)
                    move_comp->_coo._x -= x_right_diff - Component::XMAX;
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
                    this->putEntityInGrid(comp, entity, data._systemEntity);
                }
                playerCheckPosition(*entity);
            }
        }

        
    }
}
