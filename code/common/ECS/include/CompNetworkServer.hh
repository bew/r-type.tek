/**
 * @file CompNetworkServer.hh
 * @author Tookie.
 * @brief component use by server to communicate with clients.
 */

#pragma once

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

        class CompNetworkServer
        {
        public:
            /**
             * Constructor of CompNetworkServer
             */
            CompNetworkServer();

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
             * represents the server UDP
             */
            network::ServerUDP _server;
        };

    }
}
