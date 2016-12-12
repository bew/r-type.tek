/**
 * @file ASocket.hh
 * @author Tookie
 * @brief abstraction socket
 */

#pragma once

#include <string>

namespace network {
    class ASocket;
}


#ifdef __linux__
#define Socket_t int

#elif defined _WIN32
#define Socket_t SOCKET

#endif

#include "NetworkSelect.hh"

#define SERVER_ADDR "127.0.0.1"

/**
 * namespace that contains all network abstraction
 */
namespace network {

    /**
     * Representation of socket abstraction
     */
    class ASocket {
    public:

        /**
         * Constructor of ASocket
         * @param port port use to socket connection
         */
        ASocket(unsigned short port);

        /**
         *  bind socket
         */
        virtual void bind() = 0;

        /**
         * close socket
         */
        virtual void close() = 0;

        /**
         * @return private socket variable
         */
        Socket_t getSocket() const;

    protected:

        /**
         * contain the socket
         */
        Socket_t _socket;

        /*
         * contain select encapsulation
         */
        NetworkSelect _selector;

        /*
         * port use to socket connection
         */
        const unsigned short _port;
    };

}