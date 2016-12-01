/**
 * @file ASocketTCP.hh
 * @author Tookie
 * @brief abstraction of TCP socket
 */

#pragma once

#include "ASocket.hh"

/**
 * namespace that contains all network abstraction
 */
namespace network {

    /**
     * Representation of TCP socket abstraction
     */
    class ASocketTCP : public ASocket {

    public:
        /**
         *  Constructor of ASocketTCP
         * @params port port use to socket connection
         */
        ASocketTCP(const unsigned short);

        /**
         * encapsulation of listen system call who marks socket as a passive socket
         */
        virtual void listen() = 0;

        /**
         * encapsulation of accept system call who extracts the first connection request
         */
        virtual void accept() = 0;

        /**
         * encapsulation of connect system call who connects the socket
         */
        virtual void connect() = 0;
    };

}