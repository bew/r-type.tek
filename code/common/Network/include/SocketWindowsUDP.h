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
         * Constructor of SocketWindowsUDP
         *
         * @params port port use to socket connection
         */
        SocketWindowsUDP(unsigned short port);

        /**
         * Destructor of SocketWindowsUDP, call method close
         */
        ~SocketWindowsUDP();

        /**
         * bind socket
         *
         * @throw SocketException if bind fail
         */
        virtual void bind();

        /**
         * close the socket
         */
        virtual void close();

    private:
        /**
         * read in socket and add read message to the read buffer
         *
         * @throw SocketException if connect fail
         */
        virtual void recv();

        /**
         * write message in socket and update position of write buffer
         *
         * @param msg message that will be sent
         *
         *  @throw SocketException if send fail
         */
        virtual void send(const std::string &msg);
    };

    typedef SocketWindowsUDP SocketUDP;

}