/**
 * @file ClientTCP.hh
 * @author Tookie
 * @brief representation of Client TCP
 */


#pragma once

#include "AClient.hpp"

#ifdef __linux__

#include "SocketLinuxTCP.h"

#elif defined _WIN32
#include "SocketWindowsTCP.h"
#endif

/**
 * namespace that contains all network abstraction
 */
namespace network
{

    /**
     * Representation of ClientTCP
     */
    class ClientTCP : public AClient
    {
    public:

        /**
         * Default constructor of ClientTCP
         */
        ClientTCP();

        /**
         * Constructor of ClientTCP
         *
         * @param socket represent one socket already created
         */
        ClientTCP(Socket_t socket);

        ClientTCP(const ClientTCP &) = delete;

        ClientTCP &operator=(const ClientTCP &) = delete;

        /**
         * Destructor of ClientTcp
         */
        ~ClientTCP();

        /**
         * call close method of socket
         */
        virtual void close();

        /**
         * Connect client's socket
         *
         * @param hostInfos contains host ip address and port
         */
        void connect(SockAddr &hostInfos);

        /**
         * test if socket is writable or readable and calls send or recv
         *
         * @throw SocketException if select, recv or send failed
         */
        virtual void update();

        /**
         * add message to the write buffer
         *
         * @param msg message that will be add to buffer
         */
        virtual void addMessage(const std::string &msg);

        /**
         * getter of the socket
         * @return the socket member
         */
        SocketTCP &getSocket();

        /**
         * test if the socket is close or not
         * @return true if the socket is close else false
         */
        virtual bool isClose() const;

        /**
         * test if the socket is connected or not
         * @return true if the socket is connected, else false
         */
        bool isConnected() const;

    private:
        /**
         * Represents one socket tcp
         */
        SocketTCP _socket;

        /**
         * indicates if client is connect or not
         */
        bool _isConnected;
    };

}
