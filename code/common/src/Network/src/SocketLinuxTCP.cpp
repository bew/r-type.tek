/**
 * @file SocketLinuxTCP.cpp
 * @author Tookie
 * @brief TCP socket encapsulation for linux
 */

#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <cstring>
#include <iostream>
#include "SocketLinuxTCP.h"
#include "SocketException.hh"

namespace network
{

    SocketLinuxTCP::SocketLinuxTCP(const unsigned short port) : ASocketTCP(port)
    {
        errno = 0;
        if ((_socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
        {
            throw ("Could not create socket: " + std::to_string(errno));
        }
    }

    SocketLinuxTCP::~SocketLinuxTCP()
    {
        close();
    }

    void SocketLinuxTCP::bind()
    {
        errno = 0;
        if (::bind(_socket, reinterpret_cast<sockaddr *>(&_from), sizeof(_from)) != 0)
            throw SocketException("could not bind TCP socket: " + std::to_string(errno));
        _selector.monitor(this, NetworkSelect::READ);
    }

    void SocketLinuxTCP::listen()
    {
        errno = 0;
        if (::listen(_socket, SOMAXCONN) < 0)
            throw SocketException("Listen failed: " + std::to_string(errno));
    }

    void SocketLinuxTCP::accept()
    {
        errno = 0;
        sockaddr clientInfos;
        socklen_t clientInfosSize = sizeof(sockaddr);
        if ((_socket = ::accept(_socket, &clientInfos, &clientInfosSize)) == -1)
            throw SocketException("Accept failed: " + std::to_string(errno));
        _selector.monitor(this, NetworkSelect::READ);
    }

    void SocketLinuxTCP::connect()
    {
        errno = 0;
        _from.sin_addr.s_addr = inet_addr(SERVER_ADDR);
        if (::connect(_socket, reinterpret_cast<struct sockaddr *>(&_from), sizeof(_from)) < 0)
            throw SocketException("Connect failed: " + std::to_string(errno));
    }

    void SocketLinuxTCP::recv()
    {
        errno = 0;
        char buffer[BUFFER_SIZE];
        std::memset(buffer, 0, BUFFER_SIZE);
        socklen_t fromLen = sizeof(_from);
        ssize_t ret = ::recv(_socket, buffer, BUFFER_SIZE, 0);
        if (ret < 0)
            throw SocketException("Read from failed: " + std::to_string(errno));

        std::string msg(buffer, ret);
        msg += CR;
        _readBuffer.fill(msg);
    }

    void SocketLinuxTCP::send(std::string &msg)
    {
        errno = 0;
        ssize_t ret = ::send(_socket, msg.c_str(), msg.length(), 0);
        if (ret < 0)
            throw SocketException("Send to failed: " + std::to_string(errno));
        _writeBuffer.updatePosition(static_cast<size_t>(ret));
    }

    void SocketLinuxTCP::close()
    {
        if (_socket != -1)
        {
            ::close(_socket);
            _socket = -1;
        }
    }

}
