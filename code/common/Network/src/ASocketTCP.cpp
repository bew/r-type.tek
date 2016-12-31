/**
 * @file ASocketTCP.cpp
 * @author Tookie
 * @brief implementation of TCP socket abstraction
 */

#include "ASocketTCP.hh"

namespace network
{

    ASocketTCP::ASocketTCP() : ASocket()
    {

    }

    ASocketTCP::ASocketTCP(Socket_t socket): ASocket(socket)
    {

    }

    void ASocketTCP::getInfos(infoType type, std::string& ip, short& port) {
        struct sockaddr_in tmp;
        socklen_t size;

        size = sizeof(tmp);
        if (type == ASocketTCP::CURRENT)
            getsockname(_socket, reinterpret_cast<struct sockaddr *>(&tmp), &size);
        else
            getpeername(_socket, reinterpret_cast<struct sockaddr *>(&tmp), &size);
        ip = inet_ntoa(tmp.sin_addr);
        port = ntohs(tmp.sin_port);
    }
}