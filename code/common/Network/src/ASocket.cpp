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

    unsigned short ASocket::getPort() const {
        struct sockaddr_in addr;
        socklen_t len = sizeof(addr);
        if (!getsockname(_socket, reinterpret_cast<struct sockaddr *>(&addr), &len))
            return addr.sin_port;
        else
            return static_cast<unsigned short>(-1);
    }

}