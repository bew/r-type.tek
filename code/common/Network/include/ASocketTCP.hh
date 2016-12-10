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
         * @return message or empty string if nothing was read
         */
        virtual std::string get();

        /**
         * add message to the write buffer
         *
         * @param msg message that will be add to buffer
         */
        virtual void add(const std::string &msg);

    protected:

        /**
         * read in socket and add read message to the read buffer
         */
        virtual void recv() = 0;

        /**
         * write message in socket and update position of write buffer
         *
         * @param msg message that will be sent
         */
        virtual void send(const std::string &msg) = 0;

        /*
         * class contain all information util for connection
         */
        SockAddr _from;

        /**
         * circular buffer that contains message to send
         */
        NetworkBuffer _writeBuffer;

        /**
         * circular buffer that contains read messages
         */
        NetworkBuffer _readBuffer;
    };

}