/**
 * @file ASocket.cpp
 * @author Tookie
 * @brief abstraction socket implentation
 */

#include "ASocket.hh"

namespace network
{

    ASocket::ASocket(unsigned short port)
            : _port(port)
    {
    }


    Socket_t ASocket::getSocket() const
    {
        return _socket;
    }

}