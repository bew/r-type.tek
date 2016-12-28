/**
 * @file NetworkBuffer.cpp
 * @author Tookie
 * @brief encapsulation of circular buffer implementation
 */

#include <iostream>
#include "NetworkBuffer.hh"

namespace network
{

    std::string getMagic() {
        static std::string magic = "";
        if (magic.empty()) {
            union {
                int64_t integer;
                char bytes[8];
            } cutInteger;
            cutInteger.integer = network::magic;
            magic = std::string(cutInteger.bytes);
        }

        return magic;
    }

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
            if (this->checkMagic())
            {
                for (size_t j = 0; j < 8; ++j) {
                    _buffer[_readPosition] = -1;
                    ++_readPosition;
                    if (_readPosition == network::BUFFER_SIZE)
                        _readPosition = 0;
                    ++i;
                }
            }
            else {
                ++_readPosition;
                if (_readPosition == network::BUFFER_SIZE)
                    _readPosition = 0;
                ++i;
            }
        }
    }

    std::string NetworkBuffer::get() const
    {
        int i = 0;

        size_t readPosition = _readPosition;
        while (i < network::BUFFER_SIZE)
        {
            if (this->checkMagic())
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

    bool NetworkBuffer::checkMagic() const {
        union {
            int64_t integer;
            unsigned char bytes[8];
        } cutInteger;

        size_t readPosition = _readPosition;
        for (size_t i = 0; i < 8; ++i) {
            cutInteger.bytes[i] = static_cast<unsigned char>(_buffer[readPosition]);
            ++readPosition;
            if (readPosition == network::BUFFER_SIZE)
                readPosition = 0;
        }

        return cutInteger.integer == network::magic;
    }

    void NetworkBuffer::initBuffer()
    {
        for (int i = 0; i < network::BUFFER_SIZE; ++i)
            _buffer[i] = -1;
    }

}
