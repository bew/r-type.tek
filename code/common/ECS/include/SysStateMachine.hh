/**
 * @file SysStateMachine.hh
 * @author Tookie
 * @brief Header of System for State Machine.
 */

#pragma once

#include <iterator>
#include <fstream>
#include "World.hh"
#include "Entity.hh"
#include "ISystem.hh"
#include "CompEvent.hh"
#include "BSON/Document.hh"
#include "CompOptions.hh"
#include "Logs/Logger.hh"

namespace ECS
{
    namespace System
    {

        /**
         * System for State Machine
         */
        class SysStateMachine
        {
        public:

            /**
             * Update method
             *
             * @param world All the data about the world
             */
            virtual void update(ECS::WorldData &world);
        };

    }

}