/**
 * @file NetworkSelect.cpp
 * @author Tookie
 * @brief encapsulation of select system call
 */

#include "../include/ASocket.hh"
#include "../include/SocketException.hh"

namespace network
{

    NetworkSelect::NetworkSelect()
    {
        _readfds = _writefds = _readfds_result = _writefds_result = {0};
    }

    bool NetworkSelect::isReadable(const network::ASocket *socket) const
    {
        if (socket->getSocket() == -1)
            throw SocketException("Invalid Socket");

        return FD_ISSET(socket->getSocket(), &_readfds_result) != 0;

    }

    bool NetworkSelect::isWritable(const network::ASocket *socket) const
    {
        if (socket->getSocket() == -1)
            throw SocketException("Invalid Socket");

        return FD_ISSET(socket->getSocket(), &_writefds_result) != 0;
    }

    void NetworkSelect::monitor(const network::ASocket *socket, NetworkSelect::SelectType type)
    {
        if (socket->getSocket() == -1)
            throw SocketException("Invalid Socket");

        if (type == READ)
        {
            FD_SET(socket->getSocket(), &_readfds);
        }
        else if (type == WRITE)
        {
            FD_SET(socket->getSocket(), &_writefds);
        }

    }

    void NetworkSelect::unmonitor(const network::ASocket *socket, NetworkSelect::SelectType type)
    {
        if (socket->getSocket() == -1)
            throw SocketException("Invalid Socket");

        if (type == READ)
            FD_CLR(socket->getSocket(), &_readfds);

        else if (type == WRITE)
            FD_CLR(socket->getSocket(), &_writefds);
    }

    void NetworkSelect::select(struct timeval *timeout)
    {
        _readfds_result = _readfds;
        _writefds_result = _writefds;

        if ((::select(FD_SETSIZE, &_readfds_result, &_writefds_result, NULL, timeout)) == -1)
            throw SocketException("Select failed");
    }

}