/**
 * @file SysStateMachine.cpp
 * @author Tookie
 * @brief implementation of System for State Machine.
 */

#include "ECSLogLevel.hh"
#include "SysStateMachine.hh"
#include "Protocol/Server.hh"
#include "Network/SocketException.hh"

namespace ECS
{
    namespace System
    {
        bson::Document
        SysStateMachine::processMessage(const bson::Document &doc, Component::CompStateMachine &stateMachine,
                                        const Component::CompNetworkClient &network)
        {
            if (network.isValidActionTcp(doc["header"]["action"].getValueString()))
            {
                const std::string &action = doc["header"]["action"].getValueString();
                if (stateMachine._sm[stateMachine._currentState]->has(action))
                {
                    stateMachine._currentState = stateMachine._sm[stateMachine._currentState]->getLink(
                        action);
                    network._lastReceived = doc;
                    return protocol::answers::ok(doc["header"]["timestamp"].getValueInt64(), bson::Document());
                }
                else
                    return protocol::answers::unauthorized(doc["header"]["timestamp"].getValueInt64());
            }
            else if (doc["header"]["action"].getValueString() != "Answer")
                return protocol::answers::notFound(doc["header"]["timestamp"].getValueInt64());
            else if (doc["data"]["code"].getValueInt32() == 200
                     && !stateMachine._nextState.empty()
                     && stateMachine._sm[stateMachine._currentState]->has(stateMachine._nextState))
            {
                stateMachine._currentState = stateMachine._nextState;
                stateMachine._nextState.clear();
                network._lastReceived = doc;
            }
            else
            {
                network._lastReceived = doc;
                logs::logger[logs::ERRORS] << doc["data"]["msg"].getValueString() << std::endl;
            }

            return bson::Document();
        }

        void SysStateMachine::update(ECS::WorldData &world)
        {
            Component::CompNetworkClient *network = dynamic_cast<Component::CompNetworkClient *>(world._systemEntity.getComponent(
                Component::NETWORK_CLIENT));
            Component::CompStateMachine *stateMachine = dynamic_cast<Component::CompStateMachine *> (world._systemEntity.getComponent(
                Component::STATE_MACHINE));

            if (network && stateMachine)
            {
                network->_clientTCP.update();
                if (!network->_clientTCP.hasMessage())
                    return;
                try
                {
                    bson::Document doc;
                    try
                    {
                        doc = bson::Document(network->_clientTCP.getMessage());
                    }
                    catch (bson::BsonException &bsonError)
                    {
                        bson::Document answer = protocol::answers::badRequest(-1);
                        network->_clientTCP.addMessage(answer.getBufferString());
                        if (logs::logger.isRegister(logs::ERRORS))
                            logs::logger[logs::ERRORS] << bsonError.what() << std::endl;
                        else
                            std::cerr << bsonError.what() << std::endl;
                        return;
                    }
                    bson::Document answer;
                    if (protocol::checkMessage(doc))
                        answer = processMessage(doc, *stateMachine, *network);
                    else
                    {
                        if (doc.hasKey("header") && doc["header"].getValueType() == bson::DOCUMENT &&
                            protocol::checkTimestamp(doc["header"].getValueDocument()))
                            answer = protocol::answers::badRequest(doc["header"]["timestamp"].getValueInt64());
                        else
                            answer = protocol::answers::badRequest(-1);
                    }
                    if (!answer.isEmpty())
                        network->_clientTCP.addMessage(answer.getBufferString());
                }
                catch (network::SocketException &socketError)
                {
                    if (logs::logger.isRegister(logs::ERRORS))
                        logs::logger[logs::ERRORS] << socketError.what() << std::endl;
                    else
                        std::cerr << socketError.what() << std::endl;
                    return;
                }
                catch (bson::BsonException &bsonError)
                {
                    bson::Document answer = protocol::answers::internalServerError(-1);
                    network->_clientTCP.addMessage(answer.getBufferString());
                    if (logs::logger.isRegister(logs::ERRORS))
                        logs::logger[logs::ERRORS] << bsonError.what() << std::endl;
                    else
                        std::cerr << bsonError.what() << std::endl;
                }
                network->_clientTCP.update();
            }
        }
    }
}
