//
// Created by tookie on 12/21/16.
//

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