/**
 * @file CompNetworkServer.hh
 * @author Tookie.
 * @brief component use by server to communicate with clients.
 */

#pragma once

#include <list>
#include "AComponent.hh"
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

        class CompNetworkServer
        {
        public:
            /**
             * Constructor of CompNetworkServer
             */
            CompNetworkServer(unsigned short port, const std::string& token);

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
            std::string _token;
        };

    }
}
