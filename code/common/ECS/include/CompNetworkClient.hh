/**
 * @file CompNetworkClient.hh
 * @author Tookie.
 * @brief component use by one client to communicate with the server.
 */

#pragma once

#include "AComponent.hh"
#include "Network/ClientUDP.hh"

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
             * @return string that reprents his type
             */
            virtual const std::string& getType() const;

            /**
             * reprents one client udp
             */
            network::ClientUDP _client;
        };
    }
}
