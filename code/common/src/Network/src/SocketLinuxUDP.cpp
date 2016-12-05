/**
 * @file SocketLinuxUDP.cpp
 * @author Tookie
 * @brief UDP socket encapsulation for linux
 */

#include <unistd.h>
#include <netdb.h>
#include <cstring>
#include <iostream>
#include "../include/SocketLunixUDP.h"
#include "../include/SocketException.hh"

namespace network
{

    SocketLinuxUDP::SocketLinuxUDP(const unsigned short port) : ASocketUDP(port)
    {
        _socket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (_socket == -1)
            throw ("Could not create socket, error code: " + std::to_string(errno));
    }

    SocketLinuxUDP::~SocketLinuxUDP()
    {
        close();
    }

    void SocketLinuxUDP::bind()
    {
        if (::bind(_socket, reinterpret_cast<sockaddr *>(&_from), sizeof(_from)))
            throw SocketException("could not bind UDP socket, error code: " + std::to_string(errno));
        _selector.monitor(this, NetworkSelect::READ);
    }

    void SocketLinuxUDP::recv()
    {
        char buffer[BUFFER_SIZE];
        std::memset(buffer, 0, BUFFER_SIZE);
        socklen_t fromLen = sizeof(_from);
        ssize_t ret = ::recvfrom(_socket, buffer, BUFFER_SIZE, 0, reinterpret_cast<sockaddr *>(&_from), &fromLen);
        if (ret < 0)
            throw SocketException("Read from failed with error: " + std::to_string(errno));

        std::string msg(buffer, ret);
        msg += CR;
        _readBuffer.fill(msg);
    }

    void SocketLinuxUDP::send(std::string &msg)
    {
        ssize_t ret = sendto(_socket, msg.c_str(), msg.length(), 0, reinterpret_cast<sockaddr *>(&_from),
                             sizeof(_from));
        if (ret < 0)
            throw SocketException("Send to failed with error: " + std::to_string(errno));
        _writeBuffer.updatePosition(static_cast<size_t>(ret));
    }

    void SocketLinuxUDP::close()
    {
        if (_socket != -1)
        {
            ::close(_socket);
            _socket = -1;
        }
    }

}