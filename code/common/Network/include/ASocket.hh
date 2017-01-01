/**
 * @file ASocket.hh
 * @author Tookie
 * @brief abstraction socket
 */

#pragma once

#include <string>


#ifdef __linux__
#define Socket_t int

#elif defined _WIN32
#define Socket_t SOCKET

#endif

#include "SockAddr.hh"

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
         * default constructor of ASocket
         */
        ASocket();

        /**
         * Constructor of ASocketTCP
         * @param socket fd of the socket already created
         */
        ASocket(Socket_t socket);

        /**
         * bind socket
         */
        virtual void bind(SockAddr &hostInfos) = 0;

        /**
         * close socket
         */
        virtual void close() = 0;

        /**
         * @return the socket fd
         */
        Socket_t getSocket() const;

    protected:

        /**
         * represents the socket fd
         */
        Socket_t _socket;
    };

}