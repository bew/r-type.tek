/**
 * @file NetworkSelect.cpp
 * @author Tookie
 * @brief encapsulation of select system call
 */

#include <iostream>
#include "ASocket.hh"
#include "SocketException.hh"

namespace network
{

    NetworkSelect::NetworkSelect()
    {
        _readfds = _writefds = _readfds_result = _writefds_result = {0};
    }

    bool NetworkSelect::isReadable(Socket_t sockFd) const
    {
        if (sockFd == -1)
            throw SocketException("Invalid Socket");

        std::cout << "socketFd: " << sockFd << std::endl;
        std::cout << "socketFd: " << &_readfds_result << std::endl;

        return FD_ISSET(sockFd, &_readfds_result) != 0;

    }

    bool NetworkSelect::isWritable(Socket_t sockFd) const
    {
        if (sockFd == -1)
            throw SocketException("Invalid Socket");

        return FD_ISSET(sockFd, &_writefds_result) != 0;
    }

    void NetworkSelect::monitor(Socket_t sockFd, NetworkSelect::SelectType type)
    {
        if (sockFd == -1)
            throw SocketException("Invalid Socket");

        if (type == READ)
            FD_SET(sockFd, &_readfds);
        else if (type == WRITE)
            FD_SET(sockFd, &_writefds);

    }

    void NetworkSelect::unmonitor(Socket_t sockFd, NetworkSelect::SelectType type)
    {
        if (sockFd == -1)
            throw SocketException("Invalid Socket");

        if (type == READ)
            FD_CLR(sockFd, &_readfds);

        else if (type == WRITE)
            FD_CLR(sockFd, &_writefds);
    }

    void NetworkSelect::select(struct timeval *timeout)
    {
        _readfds_result = _readfds;
        _writefds_result = _writefds;

        if ((::select(FD_SETSIZE, &_readfds_result, &_writefds_result, NULL, timeout)) == -1)
            throw SocketException("Select failed");
    }

}