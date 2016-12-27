/**
 * @file SysGameNetworkClient.cpp
 * @author Tookie.
 * @brief System for client network during a game.
 */

#include "SysGameNetworkClient.hh"
#include "CompNetworkClient.hh"

namespace ECS
{
    namespace System
    {
        void SysGameNetworkClient::update(ECS::WorldData &world)
        {
            Component::CompNetworkClient *network = dynamic_cast<Component::CompNetworkClient *> (world._systemEntity.getComponent(
                Component::NETWORK_CLIENT));

            if (network)
            {
                network->_clientUDP.update();
                std::string msg = network->_clientUDP.getMessage();
                if (!msg.empty())
                {
                    bson::Document doc(msg);
                }
            }
        }
    }
}