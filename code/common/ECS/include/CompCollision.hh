/**
 * @file CompCollision.hh
 * @author Alexis.
 * @brief A collide grid in the system entity, used to check the collisions
 * only between near components.
 */

#pragma once

#include <vector>
#include "AComponent.hh"
#include "Entity.hh"

# define GRID_NB_CASES  (16)

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
        static const std::string COLLISION = "collision";

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
        class CompCollision : public AComponent {
        public:

            /**
             * structure indicating a collision between two entities.
             */
            struct Collision
            {
                Entity::Entity  *entity_a;
                Entity::Entity  *entity_b;
            };

            /**
             * Constructor
             */
            CompCollision();
            /**
             * Destructor
             */
            ~CompCollision();

            typedef std::array<std::array<std::vector<Entity::Entity *>, GRID_NB_CASES>, GRID_NB_CASES> Grid;

            /**
             * Getter for the component type.
             * @return the component type.
             */
            virtual const std::string &getType() const;

            /**
             * Add an entity in a grid cell.
             * @param x The row of the cell.
             * @param y The column of the cell.
             * @param entity The entity to be added.
             */
            void        addInGrid(unsigned x, unsigned y, Entity::Entity *entity);

            /**
             * Empty the grid.
             */
            void        flushGrid();
            
            /**
             * Grid to optimize collision calculation.
             */
            Grid        _grid;

            /**
             * To be checked after the application of the collision system, this
             * data structure contains all the collisions that happened in the frame.
             * To be flushed in the beginning of the collision system.
             */
            std::vector<Collision>   _collisions;
        };

  }
}
