
/**
 * @file SysCollision.cpp
 * @author Alexis.
 * @brief System calculating the collision of entities.
 *
 */

#include <list>
#include <iostream>

#include "ISystem.hh"
#include "CompCollision.hh"
#include "CompMovement.hh"
#include "CompHitbox.hh"
#include "SysCollision.hh"
#include "Entity.hh"
#include "World.hh"

namespace ECS {
    namespace System {

        SysCollision::SysCollision()
        {}

        SysCollision::~SysCollision()
        {}

        bool    SysCollision::valueIn(int v, int min, int max)
        {
            return (v >= min) && (v <= max);
        }

        bool    SysCollision::hitboxesOverlap(Entity::Entity *entity_a, Entity::Entity *entity_b)
        {
            Component::CompMovement *mov_a = static_cast<Component::CompMovement *>(
                entity_a->getComponent(Component::MOVEMENT));
            Component::CompHitbox *hitbox_a = static_cast<Component::CompHitbox *>(
                entity_a->getComponent(Component::HITBOX));

            Component::CompMovement *mov_b = static_cast<Component::CompMovement *>(
                entity_b->getComponent(Component::MOVEMENT));
            Component::CompHitbox *hitbox_b = static_cast<Component::CompHitbox *>(
                entity_b->getComponent(Component::HITBOX));

            bool x_overlap = false;
            bool y_overlap = false;
            
            if (mov_a && hitbox_a && mov_b && hitbox_b) {

                x_overlap = (this->valueIn(mov_a->_coo._x - hitbox_a->_midWidth,
                                           mov_b->_coo._x - hitbox_b->_midWidth,
                                           mov_b->_coo._x + hitbox_b->_midWidth)
                             || this->valueIn(mov_b->_coo._x - hitbox_b->_midWidth,
                                              mov_a->_coo._x - hitbox_a->_midWidth,
                                              mov_a->_coo._x + hitbox_a->_midWidth));

                y_overlap = (this->valueIn(mov_a->_coo._y - hitbox_a->_midHeight,
                                           mov_b->_coo._y - hitbox_b->_midHeight,
                                           mov_b->_coo._y + hitbox_b->_midHeight)
                             || this ->valueIn(mov_b->_coo._y - hitbox_b->_midHeight,
                                               mov_a->_coo._y - hitbox_a->_midHeight,
                                               mov_a->_coo._y + hitbox_a->_midHeight));
            }

            return x_overlap && y_overlap;
        }

        void    SysCollision::checkCollision(unsigned offset,
                                             std::vector<Entity::Entity *> others,
                                             std::list<Component::CompCollision::Collision> &col_list)
        {
            for (std::vector<Entity::Entity *>::iterator it = others.begin() + offset + 1;
                 it != others.end();
                 ++it)
            {
                if (this->hitboxesOverlap(others[offset], *it)) {
                    col_list.push_back({others[offset], *it});
                }
            }
        }

        void        SysCollision::update(WorldData &data)
        {
            std::list<Component::CompCollision::Collision>        collision_list;

            Component::CompCollision *collision_comp = static_cast<Component::CompCollision *>(
                data._systemEntity.getComponent(Component::COLLISION));

            if (collision_comp != nullptr) {

                for (auto &row : collision_comp->_grid)
                {
                    for (auto &column : row)
                    {

                        for (int i = 0; i < column.size(); ++i)
                        {
                            this->checkCollision(i, column, collision_list);
                        }

                    }
                }
                
                ////////////
                for (auto &e : collision_list)
                {
                    std::cout << e.entity_a << "   " << e.entity_b << std::endl;
                }
                ////////////
                
                collision_comp->flushGrid();
            }
        }
        
    }
}
