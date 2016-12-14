/**
 * @file AClient.hpp
 * @author Tookie
 * @brief abstraction client
 */

#pragma once

#include "NetworkBuffer.hh"
#include "NetworkSelect.hh"

/**
 * namespace that contains all network abstraction
 */
namespace network
{

    /**
     * Representation of client abstraction
     */
    class AClient
    {

    public:

        /**
         * Default constructor of AClient
         */
        AClient();

        /**
         * Destructor of AClient
         */
        virtual ~AClient();

        /**
         * test if socket is writable or readable and call send or recv
         */
        virtual void update() = 0;

        /**
         * add message to the write buffer
         *
         * @param msg message that will be add to buffer
         */
        virtual void addMessage(const std::string &msg) = 0;

        /**
         * get message by read buffer
         *
         * @return message or empty string if nothing was read
         */
        std::string getMessage();

        /**
         * get the NetworkBuffer use to fill or get read messages
         *
         * @return one reference to the buffer
         */
        NetworkBuffer& getReadBuffer();

        /**
         * get the NetworkBuffer use to fill or get wrotten messages
         *
         * @return one reference to the buffer
         */
        NetworkBuffer& getWriteBuffer();

        /**
         * test if the socket is close or not
         * @return true if the socket is close else false
         */
        virtual bool isClose() const = 0;

        /**
         * call close method of socket
         */
        virtual void close() = 0;
    protected:
        /**
         * Buffer use to store messages read in the socket
         */
        NetworkBuffer _readBuffer;

        /**
         * Buffer use to send message in the socket
         */
        NetworkBuffer _writeBuffer;

        /**
         * contain select encapsulation
         */
        NetworkSelect _selector;
    };

}
