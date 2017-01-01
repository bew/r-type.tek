/**
 * @file CompNetworkServer.hh
 * @author Tookie.
 * @brief component use by server to communicate with clients.
 */

#pragma once

#include <list>
#include <vector>
#include "ECS/AComponent.hh"
#include "Network/ServerUDP.hh"

/**
 * Namespace of ECS.
 */
namespace ECS
{
    /**
     * Namespace of components.
     */
    namespace Component
    {
        /**
         * Component type id.
         */
        static const std::string NETWORK_SERVER = "network server";

        /**
         * list of action received from clients on protocol UDP
         */
        static const std::list<std::string> ACTIONS_FROM_CLIENTS_UDP = {"EntityUpdate"};

        class CompNetworkServer : public AComponent
        {
        public:
            /**
             * Constructor of CompNetworkServer
             *
             * @param port port use by server
             * @param serverToken server's token
             * @param clientsToken all clients' token
             */
            CompNetworkServer(unsigned short port, const std::string& serverToken, const std::vector<std::string>& clientsToken);

            /**
             * Destructor of CompNetworkServer
             */
            ~CompNetworkServer();

            /**
             * get the type of component
             * @return string that reprents his type
             */
            virtual const std::string& getType() const;

            /**
             * check if the action is in list ACTIONS_FROM_CLIENTS_UDP
             * @param action action to check
             * @return true if action is in list, else false
             */
            static bool isValidActionUdp(const std::string &action);

            /**
             * represents the server UDP
             */
            network::ServerUDP _server;

            /**
             * contains the server's token
             */
            std::string _serverToken;

            /**
             * Stores the clients' tokens
             */
            std::vector<std::string> _clientTokens;

            /**
             * Store the port on which the UDP server run
             */
            unsigned short _port;
        };
    }
}
