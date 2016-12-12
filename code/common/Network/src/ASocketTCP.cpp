/**
 * @file ASocketTCP.cpp
 * @author Tookie
 * @brief abstraction of TCP socket
 */

#include <SocketException.hh>
#include <iostream>
#include "ASocketTCP.hh"

namespace network
{

    ASocketTCP::ASocketTCP(unsigned short port) : ASocket(port),
                                                  _from(_port)
    {

    }

    void ASocketTCP::update()
    {
        if (_buffers.empty())
            return ;
        struct timeval timer;
        timer.tv_sec = 1;
        timer.tv_usec = 0;
        _selector.select(&timer);
        size_t i = 0;
        for (auto connection : _buffers)
        {
            std::cout << i << std::endl;
            if (_selector.isReadable(connection.first))
            {
                recv(connection.first);
            }
            if (_selector.isWritable(connection.first))
            {
                std::string msg;
                if ((msg = connection.second.first.get()) != "")
                {
                    send(connection.first, msg);
                    if (connection.second.first.get() == "")
                        _selector.unmonitor(connection.first, NetworkSelect::WRITE);
                }
            }
            ++i;
        }
    }

    std::string ASocketTCP::get(Socket_t sockFd)
    {
        auto buffer = _buffers.find(sockFd);
        if (buffer == _buffers.end())
            throw SocketException("Unknown socket with fd: " + std::to_string(sockFd));
        std::string msg = buffer->second.second.get();
        buffer->second.second.updatePosition(msg.length());
        return msg;
    }

    void ASocketTCP::add(Socket_t sockFd, const std::string &msg)
    {
        auto buffer = _buffers.find(sockFd);
        if (buffer == _buffers.end())
            throw SocketException("Unknown socket with fd: " + std::to_string(sockFd));
        buffer->second.first.fill(msg);
        if (*(--msg.end()) == CR || *(--msg.end()) == LF)
            _selector.monitor(sockFd, NetworkSelect::WRITE);
    }

    std::vector<Socket_t> ASocketTCP::getConnections() const
    {
        std::vector<Socket_t> connections;

        for (auto& connection : _buffers)
            connections.push_back(connection.first);

        return connections;
    }

}