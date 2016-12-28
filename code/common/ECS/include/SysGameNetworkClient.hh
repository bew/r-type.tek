/**
 * @file SysGameNetworkClient.hh
 * @author Tookie.
 * @brief System for client network during a game.
 */

#pragma once

#include "ISystem.hh"
#include "World.hh"

namespace ECS
{
    namespace System
    {

        /**
         * System for network Client
         */
        class SysGameNetworkClient : public ISystem
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