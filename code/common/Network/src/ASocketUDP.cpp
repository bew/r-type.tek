/**
 * @file ASocketUDP.cpp
 * @author Tookie
 * @brief abstraction of UDP socket
 */

#include <string>
#include "SocketException.hh"
#include "ASocketUDP.h"

namespace network {

    ASocketUDP::ASocketUDP(unsigned short port) : ASocket(port) {

    }

    void ASocketUDP::update() {
        struct timeval timer;
        timer.tv_sec = 1;
        timer.tv_usec = 0;
        _selector.select(&timer);

        if (_selector.isReadable(_socket))
            recv();

        for (auto &buffer : _buffers) {
            if (_selector.isWritable(_socket)) {
                std::string msg;
                if ((msg = buffer.second.first.get()) != "") {
                    send(buffer.first, msg);
                    if (buffer.second.first.get() == "")
                        _selector.unmonitor(_socket, NetworkSelect::WRITE);
                }
            }
        }
    }

    std::string ASocketUDP::get(const SockAddr &hostIp) {
        auto buffer = _buffers.find(hostIp);
        if (buffer == _buffers.end()) {
            std::string error("Unknown host with address and port: ");
            error += inet_ntoa(hostIp.getAddr().sin_addr);
            error += " " + std::to_string(ntohs(hostIp.getAddr().sin_port));
            throw SocketException(error);
        }
        std::string msg = buffer->second.second.get();
        buffer->second.second.updatePosition(msg.length());
        return msg;
    }

    void ASocketUDP::add(const SockAddr &hostIp, const std::string &msg) {
        auto buffer = _buffers.find(hostIp);
        if (buffer == _buffers.end()) {
            std::string error("Unknown host with address and port: ");
            error += inet_ntoa(hostIp.getAddr().sin_addr);
            error += " " + std::to_string(ntohs(hostIp.getAddr().sin_port));
            throw SocketException(error);
        }
        buffer->second.first.fill(msg);
        if (buffer->second.first.get() != "")
            _selector.monitor(_socket, NetworkSelect::WRITE);
    }

    std::list<SockAddr> ASocketUDP::getConnections() const {
        std::list<SockAddr> connections;

        for (auto &elem : _buffers)
            connections.push_back(elem.first);

        return connections;
    }

}