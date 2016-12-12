/**
 * @file SocketWindowsTCP.hh
 * @author Tookie
 * @brief TCP socket encapsulation for windows
 */

#pragma once

#include "ASocketTCP.hh"

/**
 * namespace that contains all network abstraction
 */
namespace network {

    /**
     * Representation of TCP socket for windows
     */
    class SocketWindowsTCP : public ASocketTCP {
    public:

        /**
         * Constructor of SocketWindowsTCP
         *
         * @params port port use to socket connection
         *
         * @throw SocketException if socket couldn't be created
         */
        SocketWindowsTCP(unsigned short port);

        /**
         * Destructor of SocketWindowsTCP, call method close
         */
        ~SocketWindowsTCP();

        /**
         * bind socket
         *
         * @throw SocketException if bind fail
         */
        virtual void bind();

        /**
         * encapsulation of listen system call who marks socket as a passive socket
         *
         * @throw SocketException if listen fail
         */
        virtual void listen();

        /**
         * encapsulation of accept system call who extracts the first connection request
         *
         * @throw SocketException if accept fail
         */
        virtual void accept();

        /**
         * encapsulation of connect system call who connects the socket
         *
         * @throw SocketException if connect fail
         */
        virtual void connect();

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

    typedef SocketWindowsTCP SocketTCP;
}
