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
         * @param socket fd of the socket already created
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
        virtual void bind(SockAddr &hostInfos);

        /**
         * encapsulation of listen system call who marks socket as a passive socket
         *
         * @throw SocketException if listen fail
         */
        virtual void listen();

        /**
         * encapsulation of accept system call who extracts the first connection request
         *
         * @return new socket return by accept system call
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
        virtual void connect(SockAddr &hostInfos);

        /**
         * close the socket
         */
        virtual void close();

        /**
        * read in socket and add read message to the read buffer
        *
        * @return string read on the socket
        *
        * @throw SocketException if connect fail
        */
        virtual std::string recv();

        /**
         * write message in socket and update position of write buffer
         *
         * @param msg message that will be sent
         *
         * @return number of Bytes sent
         *
         *  @throw SocketException if send fail
         */
        virtual size_t send(const std::string &msg) const;

    };

    /**
     *  define type SocketTCP as SocketLinuxTCP
     */
    typedef SocketLinuxTCP SocketTCP;
}
