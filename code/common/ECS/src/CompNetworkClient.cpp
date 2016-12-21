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
                _client(ip, port)
        {}

        CompNetworkClient::CompNetworkClient(const network::SockAddr &addr) :
                _client(addr)
        {}

        CompNetworkClient::~CompNetworkClient()
        {}

        const std::string &CompNetworkClient::getType() const
        {
            return Component::NETWORK_CLIENT;
        }
    }
}