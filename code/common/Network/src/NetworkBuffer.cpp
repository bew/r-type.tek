/**
 * @file NetworkBuffer.cpp
 * @author Tookie
 * @brief encapsulation of circular buffer implementation
 */

#include <iostream>
#include "NetworkBuffer.hh"

namespace network
{

    NetworkBuffer::NetworkBuffer() :
            _readPosition(0), _writePosition(0)
    {
        initBuffer();
    }

    NetworkBuffer::~NetworkBuffer()
    {

    }

    void NetworkBuffer::fill(const std::string &msg)
    {
        for (char c : msg)
        {
            _buffer[_writePosition] = c;
            ++_writePosition;
            if (_writePosition == network::BUFFER_SIZE)
                _writePosition = 0;
        }
    }

    void NetworkBuffer::updatePosition(size_t length)
    {
        size_t i = 0;

        while (i < length)
        {
            ++_readPosition;
            if (_readPosition == network::BUFFER_SIZE)
                _readPosition = 0;
            ++i;
        }
        if (_buffer[_readPosition] == network::CR || _buffer[_readPosition] == network::LF || _buffer[_readPosition] == 0)
        {
            _buffer[_readPosition] = -1;
            updatePosition(1);
        }
    }

    std::string NetworkBuffer::get()
    {
        int i = 0;

        size_t readPosition = _readPosition;
        while (i < network::BUFFER_SIZE)
        {
            if (_buffer[readPosition] == network::CR || _buffer[readPosition] == network::LF)
            {
                std::string msg;
                size_t beg = _readPosition;
                while (readPosition != beg)
                {
                    msg += _buffer[beg];
                    ++beg;
                    if (beg == network::BUFFER_SIZE)
                        beg = 0;
                }
                return msg;
            }
            ++readPosition;
            if (readPosition == network::BUFFER_SIZE)
                readPosition = 0;
            ++i;
        }
        return "";
    }

    void NetworkBuffer::initBuffer()
    {
        for (int i = 0; i < network::BUFFER_SIZE; ++i)
            _buffer[i] = -1;
    }

}
