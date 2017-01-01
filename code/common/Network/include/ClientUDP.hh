/**
 * @file ClientUDP.hh
 * @author Tookie
 * @brief representation of Client UDP
 */


#pragma once

#include "AClient.hh"
#include "SockAddr.hh"

#ifdef __linux__

#include "SocketLinuxUDP.hh"

#elif defined _WIN32
#include "SocketWindowsUDP.hh"
#endif

/**
 * namespace that contains all network abstraction
 */
namespace network
{

    /**
     * Representation of ClientUDP
     */
    class ClientUDP : public AClient
    {
    public:
        /**
         * Constructor of ClientUDP
         *
         * @param ip address of the server host
         * @param port of the server host
         */
        ClientUDP(const std::string &ip, unsigned short port);

        /**
         * Constructor of ClientUDP
         *
         * @param addr class contains ip address and port of server host
         */
        ClientUDP(const SockAddr &addr);

        ClientUDP(const ClientUDP &) = delete;

        ClientUDP &operator=(const ClientUDP &) = delete;

        /**
         * Destructor of ClientUDP
         */
        virtual ~ClientUDP();

        /**
         * test if socket is writable or readable and call send or recv
         *
         * @param ms timeout in milliseconds
         * @throw SocketException if select, recv or send failed or if client receive a message by unexpected server
         */
        virtual void update(unsigned long ms = 0);

        /**
         * add message to the write buffer
         *
         * @param msg message that will be add to buffer
         */
        virtual void addMessage(const std::string &msg);

        /**
         * getter of _addr fields
         * @return the host address ip and port
         */
        SockAddr &getAddr();

        /**
         * test if the socket is close or not
         * @return true if the socket is close else false
         */
        bool isClose() const;

        /**
         * call close method of socket
         */
        virtual void close();
    private:
        /**
         * Represents host ip and port
         */
        SockAddr _addr;

        /**
         * Represents one socket udp
         */
        SocketUDP _socket;
    };

}

