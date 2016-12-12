/**
 * @file SocketLinuxUDP.cpp
 * @author Tookie
 * @brief UDP socket encapsulation for linux
 */

#include <unistd.h>
#include <netdb.h>
#include <cstring>
#include <iostream>
#include "SocketLinuxUDP.h"
#include "SocketException.hh"

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
        SockAddr from(_port);
        sockaddr_in addr = from.getAddr();
        if (::bind(_socket, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)))
            throw SocketException("could not bind UDP socket, error code: " + std::to_string(errno));
        _selector.monitor(_socket, NetworkSelect::READ);
    }

    void SocketLinuxUDP::recv()
    {
        char buffer[BUFFER_SIZE];
        sockaddr_in from;

        std::memset(buffer, 0, BUFFER_SIZE);
        socklen_t fromLen = sizeof(from);
        std::memset(&from, 0, fromLen);

        ssize_t ret = ::recvfrom(_socket, buffer, BUFFER_SIZE, 0, reinterpret_cast<sockaddr *>(&from), &fromLen);
        if (ret < 0)
            throw SocketException("Read from failed with error: " + std::to_string(errno));

        std::string msg(buffer, ret);
        SockAddr addr(ntohs(from.sin_port), inet_ntoa(from.sin_addr));
        if (_buffers.find(addr) == _buffers.end())
        {
            NetworkBuffer writeBuffer;
            NetworkBuffer readBuffer;
            _buffers.insert(std::pair<SockAddr, std::pair<NetworkBuffer, NetworkBuffer> >(addr,
                                                                                          std::pair<NetworkBuffer, NetworkBuffer>(
                                                                                                  writeBuffer,
                                                                                                  readBuffer)));
        }
        msg += CR;
        _buffers.find(addr)->second.second.fill(msg);
    }

    void SocketLinuxUDP::send(const SockAddr &hostInfos, const std::string &msg)
    {
        auto writeBuffer = _buffers.find(hostInfos);
        if (writeBuffer == _buffers.end())
        {
            std::string error("Unknown host with address and port: ");
            error += inet_ntoa(hostInfos.getAddr().sin_addr);
            error += " " + std::to_string(ntohs(hostInfos.getAddr().sin_port));
            throw SocketException(error);
        }

        sockaddr_in addr = hostInfos.getAddr();

        ssize_t ret = sendto(_socket, msg.c_str(), msg.length(), 0, reinterpret_cast<sockaddr *>(&addr),
                             sizeof(addr));
        if (ret < 0)
            throw SocketException("Send to failed with error: " + std::to_string(errno));
        writeBuffer->second.first.updatePosition(static_cast<size_t>(ret));
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