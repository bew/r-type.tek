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

}