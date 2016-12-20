/**
 * @file CompCollideGrid.cpp
 * @author Alexis.
 * @brief A collide grid in the system entity, used to check the collisions
 * only between near components.
 */

#include "CompCollideGrid.hh"

namespace ECS {
    namespace Component {

        CompCollideGrid::CompCollideGrid()
        {}

        CompCollideGrid::~CompCollideGrid()
        {}
        
        const std::string &CompCollideGrid::getType() const
        {
            return COLLIDEGRID;
        }

        void        CompCollideGrid::addInGrid(unsigned x, unsigned y, Entity::Entity *entity)
        {
            _grid[y][x].push_back(entity);
        }

        void        CompCollideGrid::flushGrid()
        {
            for (auto &row : _grid)
                for (auto &column : row)
                    column.clear();
        }
    }
}
