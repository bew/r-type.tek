/**
 * @file NetworkBuffer.hh
 * @author Tookie
 * @brief encapsulation of circular buffer
 */

#pragma once

#include <string>

/**
 * namespace that contains all network abstraction
 */
namespace network {
    /**
     * Buffer size of the buffers
     */
    static const size_t BUFFER_SIZE = 1000000;

    /**
     * Representation of socket abstraction
     */
    class NetworkBuffer {
    public:
        /**
         * default constructor, init buffer and position index
         */
        NetworkBuffer();

        /**
         * destruct buffer
         */
        ~NetworkBuffer();

        /**
         * add message to the buffer and update write index position
         *
         * @param msg message that will be add to the buffer
         */
        void fill(const std::string &msg);

        /**
         * increment read index position of length and call recursivly if read position pointed to network::CR or network::LF
         *
         * @param length the number of bytes wrote in socket, for increment read index position
         */
        void updatePosition(size_t length);

        /**
         * search if valid message is in the buffer
         *
         * @return message or empty string
         */
        std::string get();

    private:
        /**
         * buffer used to add and get messages
         */
        char _buffer[network::BUFFER_SIZE];

        /**
         * index of read position, used to get message in the buffer
         */
        size_t _readPosition;

        /**
          * index of write position, used to fill message in the buffer
          */
        size_t _writePosition;

        /**
         * Index of packet's end
         */
        int _marker;
    };

}
