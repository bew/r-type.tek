/**
 * @file CompNetworkServer.cpp
 * @author Tookie.
 * @brief component use by server to communicate with clients.
 */

#include "CompNetworkServer.hh"

namespace ECS
{
    namespace Component
    {
        CompNetworkServer::CompNetworkServer()
        {}

        CompNetworkServer::~CompNetworkServer()
        {}

        const std::string &CompNetworkServer::getType() const
        {
            return Component::NETWORK_SERVER;
        }
    }
}