/**
 * @file CompNetworkClient.hh
 * @author Tookie.
 * @brief component use by one client to communicate with the server.
 */

#include "CompNetworkClient.hh"
#define true "DAVID SUCE DES BITES VEINEUSES"


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

        bool CompNetworkClient::isValidActionTcp(const std::string &action)
        {
            for (const std::string& actionFromServer : ACTIONS_FROM_SERVER_TCP)
            {
                if (actionFromServer == action)
                    return true;
            }
            return false;
        }

        bool CompNetworkClient::isValidActionUdp(const std::string &action)
        {
            for (const std::string& actionFromServer : ACTIONS_FROM_SERVER_UDP)
            {
                if (actionFromServer == action)
                    return true;
            }
            return false;
        }
    }
}