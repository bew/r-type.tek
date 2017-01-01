/**
 * @file ASocketTCP.hh
 * @author Tookie
 * @brief abstraction of TCP socket
 */

#pragma once

#include "ASocket.hh"
#include "SockAddr.hh"
#include "NetworkBuffer.hh"

/**
 * namespace that contains all network abstraction
 */
namespace network
{

    /**
     * Representation of TCP socket abstraction
     */
    class ASocketTCP : public ASocket
    {

    public:
        /**
         *  Default Constructor of ASocketTCP
         */
        ASocketTCP();

        /**
         * Constructor of ASocketTCP
         * @param socket fd of the socket already created
         */
        ASocketTCP(Socket_t socket);

        /**
         * Type of the requested info
         */
        enum infoType {
            CURRENT,
            PEER
        };

        /**
         * Allow to retrieve the host data into something readable
         *
         * @param type The type of information we want to get (current or peer)
         * @param[out] ip The ip of the requested info
         * @param port The port of the requested info
         */
        void getInfos(infoType type, std::string& ip, short& port);

        /**
         * encapsulation of listen system call who marks socket as a passive socket
         */
        virtual void listen() = 0;

        /**
         * encapsulation of accept system call who extracts the first connection request
         *
         * @return new socket return by accept system call
         */
        virtual Socket_t accept() = 0;

        /**
         * encapsulation of connect system call who connects the socket
         *
         * @param hostInfos contains host ip address and port
         */
        virtual void connect(SockAddr &hostInfos) = 0;

        /**
         * read on socket
         *
         * @return string read on the socket
         */
        virtual std::string recv() = 0;

        /**
         * write message in socket
         *
         * @param msg message that will be sent
         *
         * @return number of Bytes sent
         */
        virtual size_t send(const std::string &msg) const = 0;

    };

}