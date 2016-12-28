/**
 * @file ServerTCP.hh
 * @author Tookie
 * @brief representation of server tcp
 */

#pragma once

#ifdef __linux__

#include "SocketLinuxTCP.hh"

#elif defined _WIN32
#include "SocketWindowsTCP.hh"
#endif

#include <vector>
#include <memory>
#include "AServer.hh"
#include "ClientTCP.hh"

/**
 * namespace that contains all network abstraction
 */
namespace network
{

    /**
     * Representation of Server TCP
     */
    class ServerTCP: public AServer
    {
    public:

        /**
         * Default constructor of ServerTCP
         */
        ServerTCP();

        ServerTCP(const ServerTCP &) = delete;

        ServerTCP &operator=(const ServerTCP &) = delete;

        /**
         * Destructor of ServerTCP
         */
        virtual ~ServerTCP();

        /**
         * test if sockets are writable or readable and call send or recv
         *
         * @param ms timeout in milliseconds
         * @throw SocketException if select, recv or send failed
         */
        virtual void update(unsigned long ms = 1);

        /**
         * call the bind method of SocketTCP
         * @param hostInfos SockAddr pass to bind method
         */
        virtual void bind(SockAddr &hostInfos);

        /**
         * call the listen method of SocketTCP
         */
        void listen();

        /**
         * call the accept method of SocketTCP
         *
         * @return new socket return by accept system call
         */
        void accept();

        /**
         *
         * pop a message to the client read buffer
         * @param client pointer to one clientTCP
         *
         * @return string that contains the first valid message on client read buffer
         */
        std::string getMessage(const std::shared_ptr<ClientTCP> client);

        /**
         * append a message to the client write buffer
         *
         * @param client pointer to one ClientTCP
         * @param message string that will be add to the client write buffer
         */
        void addMessage(const std::shared_ptr<ClientTCP> client, const std::string &message);

        /**
         * get the list of client connected
         * @return const reference to the vector of pointer to ClientTCP
         */
        const std::vector<std::shared_ptr<ClientTCP> > &getConnections() const;

        /**
         * call close method of socket
         */
        virtual void close();

        /**
         * test if the socket is close or not
         * @return true if the socket is close else false
         */
        virtual bool isClose() const;

        /**
         * get the first client who has received a message
         * @return shared ptr to a client, empty if no one has received nothing
         */
        std::shared_ptr<ClientTCP> getFirstClientWithMessage() const;

        /**
         * test if the client has received a message or not
         * @param client pointer to one ClientTCP
         * @return true if the client has received a message, else false
         */
        bool hasMessage(std::shared_ptr<ClientTCP> client) const;

    private:

        /**
         * Represent socket server
         */
        SocketTCP _socketServer;

        /**
         * contains all clients connected
         */
        std::vector<std::shared_ptr<ClientTCP> > _clients;
    };

}