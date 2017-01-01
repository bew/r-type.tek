/**
 * @file NetworkBuffer.cpp
 * @author Tookie
 * @brief encapsulation of circular buffer implementation
 */

#include <iostream>
#include "Endianess.hh"
#include "NetworkBuffer.hh"

namespace network
{
    NetworkBuffer::NetworkBuffer() :
        _readPosition(0), _writePosition(0), _marker(-1)
    {
        for (size_t i = 0; i < network::BUFFER_SIZE; ++i)
            _buffer[i] = -1;
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
            if (_readPosition == _marker)
                _marker = -1;
            _buffer[_readPosition] = -1;
            ++_readPosition;
            if (_readPosition == network::BUFFER_SIZE)
                _readPosition = 0;
            ++i;
        }
    }

    std::string NetworkBuffer::get()
    {
        size_t readPosition = _readPosition;

        if (_marker == -1) {
            union {
                int32_t integer;
                char bytes[4];
            } size;

            for (size_t i = 0; i < 4; ++i) {
                if (_buffer[readPosition] == -1)
                    return "";
                size.bytes[i] = _buffer[readPosition];
                ++readPosition;
                if (readPosition == network::BUFFER_SIZE)
                    readPosition = 0;
            }
            if (IS_BIG_ENDIAN)
                size.integer = swap_endian<int32_t>(size.integer);

            if (size.integer > network::BUFFER_SIZE)
                return "";

            _marker = _readPosition + (size.integer - 1);
            if (_marker >= network::BUFFER_SIZE)
                _marker -= network::BUFFER_SIZE;
            if (_marker < 0)
                _marker = 0;

            readPosition = _readPosition;
        }

        if (_buffer[_marker] == -1)
            return "";


        std::string msg = "";
        while (readPosition != _marker)
        {
            msg += _buffer[readPosition];
            ++readPosition;
            if (readPosition == network::BUFFER_SIZE)
                readPosition = 0;
        }
        msg += _buffer[readPosition];

        return msg;
    }

}
