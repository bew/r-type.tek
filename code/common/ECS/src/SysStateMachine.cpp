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
                bson::Document answer;

                if (protocol::checkMessage(doc))
                {
                    if (network->isValidActionTcp(doc["header"]["action"].getValueString()))
                    {
                        std::string action = doc["header"]["action"].getValueString();
                        if (stateMachine->_sm[stateMachine->_currentState]->has(action))
                        {
                            stateMachine->_currentState = stateMachine->_sm[stateMachine->_currentState]->getLink(
                                action);
                            answer = protocol::answers::ok(doc["header"]["timestamp"].getValueInt64(), answer);
                        }
                        else
                            answer = protocol::answers::unauthorized(doc["header"]["timestamp"].getValueInt64());
                    }
                    else if (doc["header"]["action"].getValueString() != "Answer")
                        answer = protocol::answers::notFound(doc["header"]["timestamp"].getValueInt64());
                }
                else if (!doc.isEmpty())
                {
                    if (doc.hasKey("header") && doc["header"].getValueDocument().hasKey("timestamp"))
                        answer = protocol::answers::badRequest(doc["header"]["timestamp"].getValueInt64());
                    else
                        answer = protocol::answers::badRequest(-1);
                }
                if (!answer.isEmpty())
                {
                    network->_clientTCP.addMessage(answer.getBufferString());
                    network->_clientTCP.update();
                }
            }
        }
    }
}
