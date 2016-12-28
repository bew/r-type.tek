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
#include "Logs/Logger.hh"
#include "CompNetworkClient.hh"
#include "CompStateMachine.hh"

namespace ECS
{
    namespace System
    {

        /**
         * System for State Machine
         */
        class SysStateMachine: public ISystem
        {
        public:

            /**
             * Update method
             *
             * @param world All the data about the world
             */
            virtual void update(ECS::WorldData &world);

            /**
             * process and analyse the message received
             * @param doc Document that contains the message received
             * @param stateMachine component use to pass to next state
             * @param network component use to receive and send message
             * @return Document that contains the answer
             */
            bson::Document processMessage(const bson::Document& doc, Component::CompStateMachine& stateMachine, const Component::CompNetworkClient& network);

        };

    }

}
