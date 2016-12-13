/**
 * @file SockAddr.hh
 * @author Tookie
 * @brief encapsulation of sockaddr_in type
 */


#pragma once


#ifdef __linux__
#include <arpa/inet.h>

#include <netinet/in.h>

#elif defined _WIN32

#include<winsock2.h>

#endif

#include <string>

/**
 * namespace that contains all network abstraction
 */
namespace network {

    /**
     * Representation of sockaddr_in encapsulation
     */
    class SockAddr {
    public:

        /**
         * Constructor of SockAddr
         * @param port port use to socket connection
         * @param addr ip of host
         */
        SockAddr(unsigned short port, const std::string &addr);

        /**
         * Constructor of SockAddr
         * @param port port use to socket connection
         */
        SockAddr(unsigned short port);

        /**
         * Destructor of SockAddr
         */
        ~SockAddr() {};

        /**
         * getter the sockaddr_in structure
         * @return the sockaddr_in structure
         */
        sockaddr_in getAddr() const;

        /**
         * set ip of host
         * @param addr ip of host
         */
        void setIPAddr(const std::string &addr);

        /**
         * Compare two Sockaddr. Use to store Sockaddr in std map
         * @param rhs Sockaddr that will be comparated with this
         * @return true if ip and port of are less than rhs else false
         */
        bool operator<(const SockAddr& rhs) const;

        bool operator==(const SockAddr& rhs) const;

        bool operator!=(const SockAddr& rhs) const;

        void setAddr(const sockaddr_in& addr);

    private:

        /**
         * sockadd_in structure that contains all information uses for connection with host
         */
        sockaddr_in _addr;
    };

}

