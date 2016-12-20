
/**
 * @file SysMovement.hh
 * @author Alexis.
 * @brief System updating the movement of entities.
 *
 */

#pragma once
#include "ISystem.hh"
#include "CompMovement.hh"

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
             * Update a single CompMovement.
             * @param component The movement component.
             */
            static void computeNextCoordinates(Component::CompMovement *component);
        };
    }
}
