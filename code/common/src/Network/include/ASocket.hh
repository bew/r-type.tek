/**
 * @file ASocket.hh
 * @author Tookie
 * @brief abstraction socket
 */

#pragma once

#include <string>
#include<winsock2.h>

namespace network {
    class ASocket;
}

#include "NetworkBuffer.hh"
#include "NetworkSelect.hh"

#ifdef __linux__
#define Socket_t int

#include <netinet/in.h>
#elif defined _WIN32
#define Socket_t long long


#endif

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
         * @brief Constructor of ASocket
         * @params port port use to socket connection
         */
        ASocket(const unsigned short port);

        /**
         * @brief bind socket
         */
        virtual void bind() = 0;

        /**
         * @brief test if socket is writable or readable and calls send or recv
         */
        virtual void update();

        /**
         * @brief get message by read buffer
         * @return message or empty string if nothing was read
         */
        virtual std::string get();

        /**
         * @brief add message to the write buffer
         * @param msg message that will be add to buffer
         */
        virtual void add(const std::string &msg);

        /**
         * @brief close socket
         */
        virtual void close() = 0;

        /**
         * @return private socket variable
         */
        Socket_t getSocket() const;

    protected:

        /**
         * @brief read in socket and add read message to the read buffer
         */
        virtual void recv() = 0;

        /**
         * @brief write message in socket and update position of write buffer
         * @param msg message that will be sent
         */
        virtual void send(std::string &msg) = 0;

        /**
         * contain the socket
         */
        Socket_t _socket;

        /**
         * circular buffer that contains read messages
         */
        NetworkBuffer _readBuffer;

        /**
         * circular buffer that contains message to send
         */
        NetworkBuffer _writeBuffer;

        /*
         * contain select encapsulation
         */
        NetworkSelect _selector;

        /*
         * port use to socket connection
         */
        const unsigned short _port;

        /*
         * struct contain all information util for connection
         */
        sockaddr_in _from;
    };

}