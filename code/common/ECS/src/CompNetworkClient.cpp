/**
 * @file CompNetworkClient.hh
 * @author Tookie.
 * @brief component use by one client to communicate with the server.
 */

#include "CompNetworkClient.hh"

namespace ECS
{
    namespace Component
    {
        CompNetworkClient::CompNetworkClient(const std::string &ip, unsigned short port) :
            _clientUDP(ip, port), _clientTCP()
        {}

        CompNetworkClient::CompNetworkClient(const network::SockAddr &addr) :
            _clientUDP(addr), _clientTCP()
        {}

        CompNetworkClient::~CompNetworkClient()
        {
        }

        const std::string &CompNetworkClient::getType() const
        {
            return Component::NETWORK_CLIENT;
        }

        bool CompNetworkClient::isValidAction(const std::string &action)
        {
            for (std::string actionFromServer : ACTIONS_FROM_SERVER)
            {
                if (actionFromServer == action)
                    return true;
            }
            return false;
        }
    }
}