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
    }
}