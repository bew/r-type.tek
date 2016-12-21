/**
 * @file AClient.cpp
 * @author Tookie
 * @brief implementation of client abstraction
 */

#include "AClient.hh"

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

    bool AClient::hasMessage() const
    {
        return (!_readBuffer.get().empty());
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
