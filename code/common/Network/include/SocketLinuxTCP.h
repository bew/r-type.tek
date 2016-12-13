/**
 * @file SocketLinuxTCP.hh
 * @author Tookie
 * @brief TCP socket encapsulation for linux
 */

#pragma once

#include "ASocketTCP.hh"

/**
 * namespace that contains all network abstraction
 */
namespace network
{

    /**
     * Representation of TCP socket for linux
     */
    class SocketLinuxTCP : public ASocketTCP
    {
    public:

        /**
         * Default constructor of SocketLinuxTCP
         *
         * @throw SocketException if socket couldn't be created
         */
        SocketLinuxTCP();

        /**
         * Constructor of SocketLinuxTCP
         *
         * @params socket fd of the socket already created
         */
        SocketLinuxTCP(Socket_t socket);

        /**
         * Destructor of SocketLinuxTCP, call method close
         */
        ~SocketLinuxTCP();

        /**
         * bind socket
         *
         * @param hostInfos contains host ip and port
         *
         * @throw SocketException if bind fail
         */
        virtual void bind(const SockAddr &hostInfos);

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
        virtual Socket_t accept();

        /**
         * encapsulation of connect system call who connects the socket
         *
         * @param hostInfos contains host ip and port
         *
         * @throw SocketException if connect fail
         */
        virtual void connect(const SockAddr &hostInfos);

        /**
         * close the socket
         */
        virtual void close();

        /**
        * read in socket and add read message to the read buffer
        *
        * @throw SocketException if connect fail
        */
        virtual std::string recv();

        /**
         * write message in socket and update position of write buffer
         *
         * @param msg message that will be sent
         *
         *  @throw SocketException if send fail
         */
        virtual int send(const std::string &msg) const;

    };

    typedef SocketLinuxTCP SocketTCP;
}
