/**
 * @file ASocket.cpp
 * @author Tookie
 * @brief abstraction socket implentation
 */

#include "ASocket.hh"

namespace network
{
    ASocket::ASocket(): _socket(-1)
    {
    }

    ASocket::ASocket(Socket_t socket): _socket(socket)
    {

    }

    Socket_t ASocket::getSocket() const
    {
        return _socket;
    }

}