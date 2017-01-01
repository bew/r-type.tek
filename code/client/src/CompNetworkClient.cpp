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
        CompNetworkClient::CompNetworkClient(const std::string &paddress, unsigned short port) :
            _clientUDP(nullptr), _clientTCP()
        {
	  _address = paddress;
	  network::SockAddr addr(port, _address);
	  _clientTCP.connect(addr);
	}

        CompNetworkClient::CompNetworkClient(const network::SockAddr &addr) :
            _clientUDP(nullptr), _clientTCP()
        {}

        CompNetworkClient::~CompNetworkClient()
        {
	  delete _clientUDP;
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
