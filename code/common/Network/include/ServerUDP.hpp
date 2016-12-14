/**
 * @file ServerUDP.hpp
 * @author Tookie
 * @brief representation of server udp
 */

#pragma once

#include <vector>
#include <memory>
#include "AServer.hpp"
#include "ClientUDP.hpp"

#ifdef __linux__

#include "SocketLinuxUDP.h"

#elif defined _WIN32
#include "SocketWindowsUDP.h"
#endif

/**
 * namespace that contains all network abstraction
 */
namespace network
{

    /**
     * Representation of Server USP
     */
    class ServerUDP : public AServer
    {
    public:
        /**
         * Default constructor of ServerUDP
         */
        ServerUDP();

        ServerUDP(const ServerUDP &) = delete;

        ServerUDP &operator=(const ServerUDP &) = delete;

        /**
         * Destructor of ServerUDP
         */
        virtual ~ServerUDP();

        /**
         * call the bind method of SocketUDP
         * @param hostInfos SockAddr pass to bind method
         */
        virtual void bind(const SockAddr &hostInfos);

        /**
         * test if socket is writable or readable and calls send or recv
         *
         * @throw SocketException if select, recv or send failed
         */
        virtual void update();

        /**
         * append a message to the client write buffer
         *
         * @param client pointer to one ClientTCP
         * @param message string that will be add to the client write buffer
         */
        void addMessage(const std::shared_ptr<ClientUDP> client, const std::string &msg);

        /**
         *
         * pop a message to the client read buffer
         * @param client pointer to one clientTCP
         *
         * @return string that contains the first valid message on client read buffer
         */
        std::string getMessage(const std::shared_ptr<ClientUDP> client);

        /**
         * get the list of client connected
         * @return const reference to the vector of pointer to ClientTCP
         */
        const std::vector<std::shared_ptr<ClientUDP> >& getConnections() const;

        /**
         * Test if the addr is unknown or not
         * @param addr of one client
         * @return true if is a new client, else false
         */
        bool isNewClient(const SockAddr &addr);

        /**
         * get Client who has the same addr than parameter
         * @param addr client ip and port for retrieve client in vector
         * @return pointer to the client who has this addr
         */
        std::shared_ptr<ClientUDP> getClient(const SockAddr &addr);

        /**
         * call close method of socket
         */
        virtual void close();

        /**
         * test if the socket is close or not
         * @return true if the socket is close else false
         */
        virtual bool isClose() const;

    private:
        /**
         * Represents one socket tcp
         */
        SocketUDP _socket;

        /**
         * contains all clients connected
         */
        std::vector<std::shared_ptr<ClientUDP> > _clients;
    };

}
