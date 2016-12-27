/**
 * @file SysGameNetworkServer.hh
 * @author Tookie.
 * @brief System for server network during a game.
 */

#include "CompNetworkServer.hh"
#include "SysGameNetworkServer.hh"

namespace ECS
{
    namespace System
    {

        void SysGameNetworkServer::update(ECS::WorldData &world)
        {
            Component::CompNetworkServer *network = dynamic_cast<Component::CompNetworkServer *> (world._systemEntity.getComponent(
                Component::NETWORK_SERVER));

            if (network)
            {
                network->_server.update();
                for (auto& client: network->_server.getConnections())
                {
                    std::string msg = network->_server.getMessage(client);
                    if (!msg.empty())
                    {
                        bson::Document doc(msg);
                    }
                }
            }
        }
    }
}