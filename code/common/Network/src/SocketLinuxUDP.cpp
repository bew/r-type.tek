/**
 * @file SocketLinuxUDP.cpp
 * @author Tookie
 * @brief implementation of UDP socket encapsulation for linux
 */

#include <unistd.h>
#include <netdb.h>
#include <cstring>
#include <iostream>
#include "SocketLinuxUDP.hh"
#include "SocketException.hh"

namespace network
{

    SocketLinuxUDP::SocketLinuxUDP() : ASocketUDP()
    {
        _socket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (_socket == -1)
            throw (std::string("Could not create socket, error code: ") + strerror(errno));
    }

    SocketLinuxUDP::~SocketLinuxUDP()
    {
        close();
    }

    void SocketLinuxUDP::bind(SockAddr &hostInfos)
    {
        int enable = 1;
        if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) != 0)
            throw SocketException(std::string("could not bind UDP socket: ") + strerror(errno));

        sockaddr_in & addr = hostInfos.getAddr();
        if (::bind(_socket, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)))
            throw SocketException(std::string("could not bind UDP socket, error code: ") + strerror(errno));

        socklen_t len = sizeof(addr);
        ::getsockname(_socket, reinterpret_cast<sockaddr *>(&addr), &len);
    }

    std::string SocketLinuxUDP::recv(SockAddr& from)
    {
        char buffer[network::BUFFER_SIZE];
        sockaddr_in fromStruct;

        std::memset(buffer, 0, network::BUFFER_SIZE);
        socklen_t fromLen = sizeof(fromStruct);
        std::memset(&fromStruct, 0, fromLen);

        ssize_t ret = ::recvfrom(_socket, buffer, network::BUFFER_SIZE, 0, reinterpret_cast<sockaddr *>(&fromStruct), &fromLen);
        if (ret < 0)
            throw SocketException(std::string("Read from failed with error: ") + strerror(errno));

        from.setAddr(fromStruct);
        std::string msg(buffer, ret);
        return msg;
    }

    size_t SocketLinuxUDP::send(const SockAddr &hostInfos, const std::string &msg)
    {
        sockaddr_in addr = hostInfos.getAddr();

        ssize_t ret = sendto(_socket, msg.c_str(), msg.length(), 0, reinterpret_cast<sockaddr *>(&addr),
                             sizeof(addr));
        if (ret < 0)
            throw SocketException(std::string("Send to failed with error: ") + strerror(errno));
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
