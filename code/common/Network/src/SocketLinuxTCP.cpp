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
        _selector.monitor(this, NetworkSelect::READ);
    }

    void SocketLinuxTCP::listen()
    {
        if (::listen(_socket, SOMAXCONN) < 0)
            throw SocketException("Listen failed: " + std::to_string(errno));
    }

    void SocketLinuxTCP::accept()
    {
        sockaddr clientInfos;
        socklen_t clientInfosSize = sizeof(sockaddr);
        if ((_socket = ::accept(_socket, &clientInfos, &clientInfosSize)) == -1)
            throw SocketException("Accept failed: " + std::to_string(errno));
        _selector.monitor(this, NetworkSelect::READ);
    }

    void SocketLinuxTCP::connect()
    {
        _from.setAddr(SERVER_ADDR);
        sockaddr_in from = _from.getAddr();
        if (::connect(_socket, reinterpret_cast<struct sockaddr *>(&from), sizeof(from)) < 0)
            throw SocketException("Connect failed: " + std::to_string(errno));
    }

    void SocketLinuxTCP::recv()
    {
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

    void SocketLinuxTCP::send(const std::string &msg)
    {
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
