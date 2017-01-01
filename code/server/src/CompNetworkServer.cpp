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
        CompNetworkServer::CompNetworkServer(unsigned short port, const std::string& serverToken, const std::vector<std::string>& clientsToken):
            _serverToken(serverToken), _clientTokens(clientsToken)
        {
            network::SockAddr addr(port);
            _server.bind(addr);
            _port = addr.getPort();
        }

        CompNetworkServer::~CompNetworkServer()
        {}

        const std::string &CompNetworkServer::getType() const
        {
            return Component::NETWORK_SERVER;
        }

        bool CompNetworkServer::isValidActionUdp(const std::string &action)
        {
            for (const std::string& actionFromClients : ACTIONS_FROM_CLIENTS_UDP)
            {
                if (actionFromClients == action)
                    return true;
            }
            return false;
        }
    }
}