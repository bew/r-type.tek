/**
 * @file CompNetworkClient.hh
 * @author Tookie.
 * @brief component use by one client to communicate with the server.
 */

#pragma once

#include <list>
#include "AComponent.hh"
#include "Network/ClientUDP.hh"
#include "Network/ClientTCP.hh"

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
        static const std::string NETWORK_CLIENT = "network client";

        /**
         * list of action received from server
         */
         static const std::list<std::string> ACTIONS_FROM_SERVER = {"EntityUpdate", "RoomJoin", "RoomLeave", "RoomKick", "GameStart", "GameLeave"};

        /**
         * representation of a component network for clients
         */
        class CompNetworkClient: public AComponent
        {
        public:
            /**
             * Constructor of CompNetworkClient
             * @param ip ip use to create client
             * @param port port use to create client
             */
            CompNetworkClient(const std::string& ip, unsigned short port);

            /**
             * Constructor of CompNetworkClient
             * @param addr address use to create the client
             */
            CompNetworkClient(const network::SockAddr& addr);

            /**
             * Destructor of CompNetworkClient
             */
            ~CompNetworkClient();

            /**
             * get the type of component
             * @return string that represents his type
             */
            virtual const std::string& getType() const;

            /**
             * check if the action is in list ACTIONS_FROM_SERVER
             * @param action action to check
             * @return true if action is in list, else false
             */
            static bool isValidAction(const std::string &action);

            /**
             * represents one client udp
             */
            network::ClientUDP _clientUDP;

            /**
             * represents one client tcp
             */
            network::ClientTCP _clientTCP;
        };
    }
}
