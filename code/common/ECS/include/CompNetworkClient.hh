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
#include "BSON/Document.hh"

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
         * list of action received from server on protocol UDP
         */
        static const std::list<std::string> ACTIONS_FROM_SERVER_UDP = {"EntityUpdate"};

        /**
         * list of action received from server on protocol TCP
         */
        static const std::list<std::string> ACTIONS_FROM_SERVER_TCP = {"RoomJoin", "RoomLeave", "RoomKick", "GameStart", "GameLeave"};

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
             * check if the action is in list ACTIONS_FROM_SERVER_TCP
             * @param action action to check
             * @return true if action is in list, else false
             */
            static bool isValidActionTcp(const std::string &action);

            /**
             * check if the action is in list ACTIONS_FROM_SERVER_UDP
             * @param action action to check
             * @return true if action is in list, else false
             */
            static bool isValidActionUdp(const std::string &action);

            /**
             * represents one client udp
             */
            network::ClientUDP _clientUDP;

            /**
             * represents one client tcp
             */
            network::ClientTCP _clientTCP;

            /**
             * Store the last packet received
             */
            bson::Document _lastReceived;
        };
    }
}
