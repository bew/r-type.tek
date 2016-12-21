/**
 * @file CompCollision.cpp
 * @author Alexis.
 * @brief A collide grid in the system entity, used to check the collisions
 * only between near components.
 */

#include "CompCollision.hh"

namespace ECS {
    namespace Component {

        CompCollision::CompCollision()
        {}

        CompCollision::~CompCollision()
        {}
        
        const std::string &CompCollision::getType() const
        {
            return COLLISION;
        }

        void        CompCollision::addInGrid(unsigned x, unsigned y, Entity::Entity *entity)
        {
            _grid[y][x].push_back(entity);
        }

        void        CompCollision::flushGrid()
        {
            for (auto &row : _grid)
                for (auto &column : row)
                    column.clear();
        }
    }
}
