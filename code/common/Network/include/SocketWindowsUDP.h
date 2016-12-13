/**
 * @file SocketWindowsUDP.hh
 * @author Tookie
 * @brief UDP socket encapsulation for windows
 */

#pragma once

#include "ASocketUDP.h"

/**
 * namespace that contains all network abstraction
 */
namespace network {

    /**
     * Representation of UDP socket for windows
     */
    class SocketWindowsUDP : public ASocketUDP {
    public:

        /**
         * Default constructor of SocketWindowsUDP
         *
         * @throw SocketException if socket couldn't be created
         */
        SocketWindowsUDP();

        /**
         * Destructor of SocketWindowsUDP, call method close
         */
        ~SocketWindowsUDP();

        /**
         * bind socket
         *
         * @throw SocketException if bind fail
         */
        virtual void bind(const SockAddr &from);

        /**
         * close the socket
         */
        virtual void close();

        /**
        * read in socket and add read message to the read buffer
        */
        virtual std::string recv(SockAddr& hostInfos);

        /**
         * write message in socket and update position of write buffer
         *
         * @param hostInfos represents the host IP address and port
         * @param msg message that will be sent
         *
         *  @throw SocketException if send fail or if the host address is unknown
         */
        virtual int send(const SockAddr &hostInfos, const std::string &msg);

    };

    typedef SocketWindowsUDP SocketUDP;

}