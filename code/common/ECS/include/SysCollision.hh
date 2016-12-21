
/**
 * @file SysCollision.hh
 * @author Alexis.
 * @brief System calculating the collision of entities.
 *
 */

#pragma once
#include "ISystem.hh"
#include "CompCollision.hh"

/**
 * Namespace of ECS.
 */
namespace ECS {

    /**
     * Namespace of systems.
     */
    namespace System {

        /**
         * System calculating the collision of entities.
         */
        class SysCollision : public ISystem
        {
        public:
            /**
             * Constructor.
             */
            SysCollision();
            /**
             * Destructor.
             */
            virtual ~SysCollision();

            /**
             * update function. Will add all colliding entities to the collision component.
             * @param data The persistent information of the ECS.
             */
            void        update(WorldData &data) override;

            /**
             * Calculate if a value is in an interval.
             * @param v The value
             * @param min The inferior boundary
             * @param max The superior boundary
             * @return true if the value is in the interval [min, max]. False otherwise.
             */
            static bool    valueIn(int v, int min, int max);

            /**
             * Calculate if a value is in an interval.
             * @param entity_a An entity.
             * @param entity_b An entity.
             * @return true if the hitboxes of the entities overlap. False otherwise.
             */
            bool    hitboxesOverlap(Entity::Entity *entity_a, Entity::Entity *entity_b);

            /**
             * Check the collisions for a given cell of the grid and add them in a list.
             * @param offset The position of the entity in the cell vector.
             * @param others The cell vector.
             * @param col_list The list where the collisions are to be added.
             */
            void    checkCollision(unsigned offset,
                                   std::vector<Entity::Entity *> others,
                                   std::list<Component::CompCollision::Collision> &col_list);

            
        };
    }
}
