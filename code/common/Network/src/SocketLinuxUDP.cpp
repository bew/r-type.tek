/**
 * @file SocketLinuxUDP.cpp
 * @author Tookie
 * @brief implementation of UDP socket encapsulation for linux
 */

#include <unistd.h>
#include <netdb.h>
#include <cstring>
#include <iostream>
#include "SocketLinuxUDP.h"
#include "SocketException.hh"

namespace network
{

    SocketLinuxUDP::SocketLinuxUDP() : ASocketUDP()
    {
        _socket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (_socket == -1)
            throw ("Could not create socket, error code: " + std::to_string(errno));
    }

    SocketLinuxUDP::~SocketLinuxUDP()
    {
        close();
    }

    void SocketLinuxUDP::bind(const SockAddr &hostInfos)
    {
        sockaddr_in addr = hostInfos.getAddr();
        if (::bind(_socket, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)))
            throw SocketException("could not bind UDP socket, error code: " + std::to_string(errno));
    }

    std::string SocketLinuxUDP::recv(SockAddr& from)
    {
        char buffer[BUFFER_SIZE];
        sockaddr_in fromStruct;

        std::memset(buffer, 0, BUFFER_SIZE);
        socklen_t fromLen = sizeof(fromStruct);
        std::memset(&fromStruct, 0, fromLen);

        ssize_t ret = ::recvfrom(_socket, buffer, BUFFER_SIZE, 0, reinterpret_cast<sockaddr *>(&fromStruct), &fromLen);
        if (ret < 0)
            throw SocketException("Read from failed with error: " + std::to_string(errno));

        from.setAddr(fromStruct);
        std::string msg(buffer, ret);
        return msg;
    }

    int SocketLinuxUDP::send(const SockAddr &hostInfos, const std::string &msg)
    {
        sockaddr_in addr = hostInfos.getAddr();

        ssize_t ret = sendto(_socket, msg.c_str(), msg.length(), 0, reinterpret_cast<sockaddr *>(&addr),
                             sizeof(addr));
        if (ret < 0)
            throw SocketException("Send to failed with error: " + std::to_string(errno));
        return ret;
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