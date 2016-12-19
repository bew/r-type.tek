/**
 * @file AClient.hpp
 * @author Tookie
 * @brief abstraction server
 */
#pragma once

#include "SockAddr.hh"
#include "NetworkSelect.hh"

/**
 * namespace that contains all network abstraction
 */
namespace network
{
    /**
     * Representation of server abstraction
     */
    class AServer
    {

    public:

        /**
         * Default constructor of AClient
         */
        AServer();

        /**
         * Destructor of AClient
         */
        virtual ~AServer();

        /**
         * test if sockets are writable or readable and call send or recv
         */
        virtual void update() = 0;

        /**
         * call the bind method of TCP or UDP Socket
         * @param hostInfos SockAddr pass to bind method
         */
        virtual void bind(SockAddr &hostInfos) = 0;

        /**
         * call close method of socket
         */
        virtual void close() = 0;
    protected:
        /**
         * contain select encapsulation
         */
        NetworkSelect _selector;
    };

}