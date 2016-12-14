/**
 * @file AClient.hpp
 * @author Tookie
 * @brief implementation of client abstraction
 */

#include "AClient.hpp"

namespace network
{
    AClient::AClient()
    {}

    AClient::~AClient()
    {}

    std::string AClient::getMessage()
    {
        std::string msg = _readBuffer.get();
        _readBuffer.updatePosition(msg.length());
        return msg;
    }

    NetworkBuffer &AClient::getReadBuffer()
    {
        return _readBuffer;
    }

    NetworkBuffer &AClient::getWriteBuffer()
    {
        return _writeBuffer;
    }
}