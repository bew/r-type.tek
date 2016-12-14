/**
* @file ASocketUDP.hh
* @author Tookie
* @brief abstraction of UDP socket
*/

#pragma once

#ifdef __linux__

#include <arpa/inet.h>

#endif

#include "ASocket.hh"
#include "SockAddr.hh"

/**
 * namespace that contains all network abstraction
 */
namespace network
{

    /**
     * Representation of UDP socket abstraction
     */
    class ASocketUDP : public ASocket
    {
    public:
        /**
         * Default constructor of ASocketUDP
         */
        ASocketUDP();

        /**
         * read on socket
         *
         * @param contains host ip address and port
         *
         * @return the string read on the socket
         */
        virtual std::string recv(SockAddr &hostInfos) = 0;

        /**
         * write message in socket
         *
         * @param hostInfos represents the host IP address and port
         * @param msg message that will be sent
         *
         * @return number of Bytes wrote on the socket
         */
        virtual size_t send(const SockAddr &hostInfos, const std::string &msg) = 0;
    };

}