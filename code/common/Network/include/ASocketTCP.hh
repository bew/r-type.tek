/**
 * @file ASocketTCP.hh
 * @author Tookie
 * @brief abstraction of TCP socket
 */

#pragma once

#include <vector>
#include <map>
#include "ASocket.hh"
#include "SockAddr.hh"
#include "NetworkBuffer.hh"


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
        ASocketTCP(unsigned short);

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


        /**
         * test if socket is writable or readable and calls send or recv
         */
        virtual void update();

        /**
         * get message by read buffer
         *
         * @param fd that represents the client connection
         * @return message or empty string if nothing was read
         */
        virtual std::string get(Socket_t sockFd);

        /**
         * add message to the write buffer
         *
         * @param fd that represents the client connection
         * @param msg message that will be add to buffer
         */
        virtual void add(Socket_t sockFd, const std::string &msg);

        std::vector<Socket_t> getConnections() const;
    protected:

        /**
         * read in socket and add read message to the read buffer
         *
         * @param fd that represents the client connection
         */
        virtual void recv(Socket_t sockFd) = 0;

        /**
         * write message in socket and update position of write buffer
         *
         * @param fd that represents the client connection
         * @param msg message that will be sent
         */
        virtual void send(Socket_t sockFd, const std::string &msg) = 0;

        /*
         * class contain all information util for connection
         */
        SockAddr _from;

        /**
         * contains all hosts IPs and two buffers for each host, first is the write buffer and second is the read buffer
         */
        std::map<Socket_t, std::pair<NetworkBuffer, NetworkBuffer> > _buffers;
    };

}