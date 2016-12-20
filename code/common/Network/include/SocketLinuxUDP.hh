/**
 * @file SocketLinuxUDP.hh
 * @author Tookie
 * @brief UDP socket encapsulation for linux
 */

#pragma once

#include "NetworkBuffer.hh"
#include "ASocketUDP.hh"

/**
 * namespace that contains all network abstraction
 */
namespace network
{

    /**
     * Representation of UDP socket for linux
     */
    class SocketLinuxUDP : public ASocketUDP
    {
    public:
        /**
         * Constructor of SocketLinuxUDP
         *
         * @throw SocketException if socket couldn't be created
         */
        SocketLinuxUDP();

        /**
         * Destructor of SocketLinuxUDP, call method close
         */
        ~SocketLinuxUDP();

        /**
         * bind socket
         *
         * @throw SocketException if bind fail
         */
        virtual void bind(SockAddr &from);

        /**
         * read in socket and add read message to the read buffer
         *
         * @return string read on the socket
         */
        virtual std::string recv(SockAddr& from);

        /**
         * write message in socket and update position of write buffer
         *
         * @param hostInfos represents the host IP address and port
         * @param msg message that will be sent
         *
         * @return number of Bytes sent
         *
         * @throw SocketException if send fail or if the host address is unknown
         */
        virtual size_t send(const SockAddr &hostInfos, const std::string &msg);

        /**
         * close the socket
         */
        virtual void close();
    };

    /**
     *  define type SocketUDP as SocketLinuxUDP
     */
    typedef SocketLinuxUDP SocketUDP;

}