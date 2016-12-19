/**
 * @file SocketLinuxTCP.cpp
 * @author Tookie
 * @brief implementation of TCP socket encapsulation for linux
 */

#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include "SocketLinuxTCP.h"
#include "SocketException.hh"

namespace network
{

    SocketLinuxTCP::SocketLinuxTCP() : ASocketTCP()
    {
        if ((_socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
            throw ("Could not create socket: " + std::to_string(errno));
    }

    SocketLinuxTCP::SocketLinuxTCP(Socket_t socket) : ASocketTCP(socket)
    {

    }

    SocketLinuxTCP::~SocketLinuxTCP()
    {
        close();
    }

    void SocketLinuxTCP::bind(const SockAddr& hostInfos)
    {
        sockaddr_in addr = hostInfos.getAddr();
        if (::bind(_socket, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) != 0)
            throw SocketException("could not bind TCP socket: " + std::to_string(errno));
    }

    void SocketLinuxTCP::listen()
    {
        if (::listen(_socket, SOMAXCONN) < 0)
            throw SocketException("Listen failed: " + std::to_string(errno));
    }

    Socket_t SocketLinuxTCP::accept()
    {
        sockaddr clientInfos;
        std::memset(&clientInfos, 0, sizeof(clientInfos));
        socklen_t clientInfosSize = sizeof(struct sockaddr_in);
        Socket_t newConnection;
        if ((newConnection = ::accept(_socket, &clientInfos, &clientInfosSize)) == -1)
            throw SocketException("Accept failed: " + std::to_string(errno));
        return newConnection;
    }

    void SocketLinuxTCP::connect(const SockAddr& hostInfos)
    {
        sockaddr_in from = hostInfos.getAddr();
        if (::connect(_socket, reinterpret_cast<struct sockaddr *>(&from), sizeof(from)) < 0)
            throw SocketException("Connect failed: " + std::to_string(errno));
    }

    std::string SocketLinuxTCP::recv()
    {
        char buffer[network::BUFFER_SIZE];
        std::memset(buffer, 0, network::BUFFER_SIZE);
        ssize_t ret = ::recv(_socket, buffer, network::BUFFER_SIZE, 0);
        if (ret < 0)
            throw SocketException("Read failed: " + std::to_string(errno));
        else if (ret == 0)
            close();
        std::string msg(buffer, ret);
        return msg;
    }

    size_t SocketLinuxTCP::send(const std::string &msg) const
    {
        ssize_t ret = ::send(_socket, msg.c_str(), msg.length(), 0);
        if (ret < 0)
            throw SocketException("Send failed: " + std::to_string(errno));
        return ret;
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
