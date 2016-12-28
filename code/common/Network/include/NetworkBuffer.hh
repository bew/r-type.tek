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
     * Magic to delimit binary buffer
     */
    static const int64_t magic = 1422602646269722845;

    /**
      * Allow to get the magic representation in string in order to end the message
      *
      * @return the magic representation in string in order to end the message
      */
    std::string getMagic();

    /**
     * Buffer size of the buffers
     */
    static const size_t BUFFER_SIZE = 4096;

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
        std::string get() const;

    private:
        /**
         * initiall all bytes of buffer to -1
         */
        void initBuffer();

        /**
         * Allow to check if the magic is the next byte to process into the buffer
         *
         * @return true if the magic is the next byte to proccess into the buffer, else false
         */
        bool checkMagic(size_t readPosition) const;

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
    };

}
