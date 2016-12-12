/**
 * @file SocketLinuxTCP.cpp
 * @author Tookie
 * @brief TCP socket encapsulation for linux
 */

#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include "SocketLinuxTCP.h"
#include "SocketException.hh"

namespace network
{

    SocketLinuxTCP::SocketLinuxTCP(unsigned short port) : ASocketTCP(port)
    {
        if ((_socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
            throw ("Could not create socket: " + std::to_string(errno));
    }

    SocketLinuxTCP::~SocketLinuxTCP()
    {
        close();
    }

    void SocketLinuxTCP::bind()
    {
        sockaddr_in addr = _from.getAddr();
        if (::bind(_socket, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) != 0)
            throw SocketException("could not bind TCP socket: " + std::to_string(errno));
    }

    void SocketLinuxTCP::listen()
    {
        if (::listen(_socket, SOMAXCONN) < 0)
            throw SocketException("Listen failed: " + std::to_string(errno));
    }

    void SocketLinuxTCP::accept()
    {
        sockaddr clientInfos;
        std::memset(&clientInfos, 0, sizeof(clientInfos));
        socklen_t clientInfosSize = sizeof(struct sockaddr_in);
        Socket_t newConnection;
        if ((newConnection = ::accept(_socket, &clientInfos, &clientInfosSize)) == -1)
            throw SocketException("Accept failed: " + std::to_string(errno));
        _selector.monitor(newConnection, NetworkSelect::READ);
        NetworkBuffer readBuffer;
        NetworkBuffer writeBuffer;
        _buffers.insert(std::pair<Socket_t, std::pair<NetworkBuffer, NetworkBuffer> >(newConnection,
                                                                                      std::pair<NetworkBuffer, NetworkBuffer>(
                                                                                              writeBuffer,
                                                                                              readBuffer)));
    }

    void SocketLinuxTCP::connect()
    {
        _from.setAddr(SERVER_ADDR);
        sockaddr_in from = _from.getAddr();
        if (::connect(_socket, reinterpret_cast<struct sockaddr *>(&from), sizeof(from)) < 0)
            throw SocketException("Connect failed: " + std::to_string(errno));
        _selector.monitor(_socket, NetworkSelect::READ);
        NetworkBuffer readBuffer;
        NetworkBuffer writeBuffer;
        _buffers.insert(std::pair<Socket_t, std::pair<NetworkBuffer, NetworkBuffer> >(_socket,
                                                                                      std::pair<NetworkBuffer, NetworkBuffer>(
                                                                                              writeBuffer,
                                                                                              readBuffer)));
    }

    void SocketLinuxTCP::recv(Socket_t sockFd)
    {
        char buffer[BUFFER_SIZE];
        std::memset(buffer, 0, BUFFER_SIZE);
        socklen_t fromLen = sizeof(_from);
        ssize_t ret = ::recv(sockFd, buffer, BUFFER_SIZE, 0);
        if (ret < 0)
            throw SocketException("Read from failed: " + std::to_string(errno));

        std::string msg(buffer, ret);
        msg += CR;
        _buffers.find(sockFd)->second.second.fill(msg);
    }

    void SocketLinuxTCP::send(Socket_t sockFd, const std::string &msg)
    {
        ssize_t ret = ::send(sockFd, msg.c_str(), msg.length(), 0);
        if (ret < 0)
            throw SocketException("Send to failed: " + std::to_string(errno));
        _buffers.find(sockFd)->second.first.updatePosition(static_cast<size_t>(ret));
    }

    void SocketLinuxTCP::close()
    {
        if (_socket != -1)
        {
            ::close(_socket);
            _socket = -1;
        }
        for (auto socket = _buffers.begin(); socket != _buffers.end(); ++socket)
        {
            ::close(socket->first);
        }
    }

}
