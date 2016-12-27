/**
 * @file SysStateMachine.cpp
 * @author Tookie
 * @brief implementation of System for State Machine.
 */

#include "SysStateMachine.hh"
#include "CompNetworkClient.hh"
#include "CompStateMachine.hh"
#include "Protocol/Server.hh"

namespace ECS
{
    namespace System
    {
        void SysStateMachine::update(ECS::WorldData &world)
        {
            Component::CompNetworkClient *network = dynamic_cast<Component::CompNetworkClient *>(world._systemEntity.getComponent(
                Component::NETWORK_CLIENT));
            Component::CompStateMachine *stateMachine = dynamic_cast<Component::CompStateMachine *> (world._systemEntity.getComponent(
                Component::STATE_MACHINE));

            if (network && stateMachine)
            {
                network->_clientTCP.update();
                bson::Document doc(network->_clientTCP.getMessage());
                if (protocol::checkMessage(doc))
                {
                    std::string action = doc["header"]["action"].getValueString();

                    if (stateMachine->_sm[stateMachine->_currentState]->has(action))
                        stateMachine->_currentState = stateMachine->_sm[stateMachine->_currentState]->getLink(action);
                }
            }
        }
    }
}
