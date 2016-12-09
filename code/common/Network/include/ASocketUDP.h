/**
* @file ASocketUDP.hh
* @author Tookie
* @brief abstraction of UDP socket
*/

#pragma once

#include <list>
#include <map>
#include "ASocket.hh"
#include "SockAddr.hh"
#include "NetworkBuffer.hh"

/**
 * namespace that contains all network abstraction
 */
namespace network {

    /**
     * Representation of UDP socket abstraction
     */
    class ASocketUDP : public ASocket {
    public:
        /**
         * Constructor of ASocketUDP
         * @param port port use to socket connection
         */
        ASocketUDP(unsigned short port);

        /**
         * test if socket is writable or readable and calls send or recv
         */
        virtual void update();

        /**
         * add message to the write buffer
         *
         * @param hostInfos represents the host IP address and port
         * @param msg message that will be add to buffer
         *
         * @throw SocketException if the host is unknown
         */
        virtual void add(const SockAddr& hostInfos, const std::string &msg);

        /**
         * get message by read buffer
         *
         * @param hostInfos represents the host IP address and port
         * @return message or empty string if nothing was read
         *
         * @throw SocketException the host is unknown
         */
        virtual std::string get(const SockAddr& hostInfos);

        std::list<SockAddr> getConnections() const;
    protected:

        /**
         * read in socket and add read message to the read buffer
         */
        virtual void recv() = 0;

        /**
         * write message in socket and update position of write buffer
         *
         * @param hostInfos represents the host IP address and port
         * @param msg message that will be sent
         */
        virtual void send(const SockAddr& hostInfos, const std::string &msg) = 0;

        /**
         * contains all hosts IPs and two buffers for each host, first is the write buffer and second is the read buffer
         */
        std::map<SockAddr, std::pair<NetworkBuffer, NetworkBuffer> > _buffers;
    };

}