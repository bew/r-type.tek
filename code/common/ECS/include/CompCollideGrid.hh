/**
 * @file CompCollideGrid.hh
 * @author Alexis.
 * @brief A collide grid in the system entity, used to check the collisions
 * only between near components.
 */

#pragma once

#include <vector>
#include "AComponent.hh"
#include "Entity.hh"

/**
 * Namespace of ECS.
 */
namespace ECS {

    /**
     * Namespace of components.
     */
    namespace Component {

        /**
         * Component type id.
         */
        static const std::string COLLIDEGRID = "collidegrid";

        /**
         * Standard width of the window.
         */
        static const unsigned XMAX = 1280;
        /**
         * Standard height of the window.
         */
        static const unsigned YMAX = 720;

        /**
         * Component to optimize collision calculation.
         */
        class CompCollideGrid : public AComponent {
        public:
            /**
             * Constructor
             */
            CompCollideGrid();
            /**
             * Destructor
             */
            ~CompCollideGrid();

            typedef std::array<std::array<std::vector<Entity::Entity *>, 16>, 16> Grid;

            /**
             * Getter for the component type.
             * @return the component type.
             */
            virtual const std::string &getType() const;

            /**
             * Add an entity in a grid cell.
             * @param y The column of the cell.
             * @param x The row of the cell.
             * @param entity The entity to be added.
             */
            void        addInGrid(unsigned y, unsigned x, Entity::Entity *entity);

            /**
             * Empty the grid.
             */
            void        flushGrid();
            
            /**
             * Grid to optimize collision calculation.
             */
            Grid        _grid;
        };

  }
}
