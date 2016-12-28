
/**
 * @file SysMovement.hh
 * @author Alexis.
 * @brief System updating the movement of entities.
 *
 */

#pragma once
#include "ISystem.hh"
#include "CompMovement.hh"
#include "Entity.hh"

/**
 * Namespace of ECS.
 */
namespace ECS {

    /**
     * Namespace of systems.
     */
    namespace System {

        /**
         * System updating the movement of entities.
         */
        class SysMovement : public ISystem
        {
        public:
            /**
             * Constructor.
             */
            SysMovement();
            /**
             * Destructor.
             */
            virtual ~SysMovement();

            
            /**
             * Put an entity in the grid.
             * @param mov_comp movement component of the given entity.
             * @param entity given entity.
             * @param sys_entity system entity of the world.
             */
            void        putEntityInGrid(Component::CompMovement *mov_comp,
                                             Entity::Entity *entity,
                                             Entity::Entity &sys_entity);
            /**
             * Update a single CompMovement.
             * @param component The movement component.
             */
            static void computeNextCoordinates(Component::CompMovement *component);

            /**
             * Check if the position is valid for a player entity.
             * ie, check that the players don't leave the screen.
             * @param player The entity. The function will check if this a player.
             */
            static void playerCheckPosition(Entity::Entity &player);

            /**
             * update function. Will update all CompMovement.
             * @param data The persistent information of the ECS.
             */
            void        update(WorldData &data) override;
        };
    }
}
