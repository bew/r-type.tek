
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
             * update function. Will update all CompMovement.
             * @param data The persistent information of the ECS.
             */
            void        update(WorldData &data) override;

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
        };
    }
}
