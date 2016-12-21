//
// Created by tookie on 12/21/16.
//

#pragma once

#include "AComponent.hh"
#include "ServerUDP.hh"

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
