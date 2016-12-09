/**
 * @file SocketWindowsUDP.cpp
 * @author Tookie
 * @brief UDP socket encapsulation for windows
 */

#include <cstring>
#include "SocketWindowsUDP.h"
#include "SocketException.hh"

namespace network {

    SocketWindowsUDP::SocketWindowsUDP(unsigned short port) : ASocketUDP(port) {
        WSAData wsd;
        if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
            throw SocketException("WSAStartup failed with error: " + std::to_string(WSAGetLastError()));

        _socket = WSASocket(AF_INET,
                            SOCK_DGRAM,
                            IPPROTO_UDP,
                            nullptr,
                            0,
                            WSA_FLAG_OVERLAPPED);

        if (_socket == INVALID_SOCKET)
            throw SocketException("WSA Socket failed with error: " + std::to_string(WSAGetLastError()));
    }

    SocketWindowsUDP::~SocketWindowsUDP() {
        close();
        WSACleanup();
    }

    void SocketWindowsUDP::bind() {
        SockAddr from(_port);
        sockaddr_in addr = from.getAddr();
        if (::bind(_socket, reinterpret_cast<SOCKADDR *>(&addr), sizeof(addr)) == SOCKET_ERROR)
            throw SocketException("bind failed with error: " + std::to_string(WSAGetLastError()));
        _selector.monitor(this, NetworkSelect::READ);
    }

    void SocketWindowsUDP::recv() {
        char bufTmp[BUFFER_SIZE];
        DWORD flag = 0;
        DWORD numberOfBytesRecv = 0;
        WSAOVERLAPPED recvOverlapped;

        WSABUF buffer;

        sockaddr_in from;
        int fromSize = sizeof(from);
        std::memset(&from, 0, fromSize);
        std::memset(bufTmp, 0, BUFFER_SIZE);
        buffer.len = BUFFER_SIZE;
        buffer.buf = bufTmp;

        recvOverlapped.hEvent = WSACreateEvent();
        if (recvOverlapped.hEvent == nullptr)
            throw SocketException("WSACreateEvent failed: " + std::to_string(WSAGetLastError()));
        int ret = WSARecvFrom(_socket, &buffer, 1, &numberOfBytesRecv, &flag, reinterpret_cast<sockaddr *>(&from),
                              &fromSize,
                              &recvOverlapped,
                              nullptr);
        if (((ret == SOCKET_ERROR) && (WSA_IO_PENDING != WSAGetLastError()))) {
            WSACloseEvent(recvOverlapped.hEvent);
            throw SocketException("recv from failed with error: " + std::to_string(WSAGetLastError()));
        }
        DWORD rc = WSAWaitForMultipleEvents(1, &recvOverlapped.hEvent, TRUE, INFINITE, TRUE);
        if (rc == WSA_WAIT_FAILED) {
            WSACloseEvent(recvOverlapped.hEvent);
            throw SocketException(
                    "Wsa wait for multiple events failed with error: " + std::to_string(WSAGetLastError()));
        }

        ret = WSAGetOverlappedResult(_socket, &recvOverlapped, &numberOfBytesRecv, FALSE, &flag);
        if (ret == FALSE) {
            WSACloseEvent(recvOverlapped.hEvent);
            throw SocketException(
                    "Wsa get overlapped result events failed with error: " + std::to_string(WSAGetLastError()));
        }

        WSACloseEvent(recvOverlapped.hEvent);

        std::string msg(buffer.buf, numberOfBytesRecv);

        SockAddr addr(ntohs(from.sin_port), inet_ntoa(from.sin_addr));
        if (_buffers.find(addr) == _buffers.end()) {
            NetworkBuffer writeBuffer;
            NetworkBuffer readBuffer;
            _buffers.insert(std::pair<SockAddr, std::pair<NetworkBuffer, NetworkBuffer> >(addr, std::pair<NetworkBuffer, NetworkBuffer>(writeBuffer, readBuffer)));
        }
        msg += CR;
        _buffers.find(addr)->second.second.fill(msg);
    }

    void SocketWindowsUDP::send(const SockAddr &hostIp, const std::string &msg) {
        WSABUF buffer;

        buffer.buf = const_cast<char *>(msg.c_str());
        buffer.len = static_cast<u_long >(msg.length());

        WSAOVERLAPPED sndOverlapped;
        DWORD flag;
        DWORD numberOfBytesSnd = 0;

        flag = 0;

        auto writeBuffer = _buffers.find(hostIp);
        if (writeBuffer == _buffers.end()) {
            std::string error("Unknown host with address and port: ");
            error += inet_ntoa(hostIp.getAddr().sin_addr);
            error += " " + std::to_string(ntohs(hostIp.getAddr().sin_port));
            throw SocketException(error);
        }

        int fromSize = sizeof(hostIp.getAddr());

        sndOverlapped.hEvent = WSACreateEvent();
        if (sndOverlapped.hEvent == nullptr) {
            throw SocketException("WSACreateEvent failed: " + std::to_string(WSAGetLastError()));
        }

        sockaddr_in addr = hostIp.getAddr();
        int ret = WSASendTo(_socket,
                            &buffer,
                            1,
                            &numberOfBytesSnd,
                            flag,
                            reinterpret_cast<SOCKADDR *>(&addr),
                            fromSize,
                            &sndOverlapped,
                            nullptr);

        if ((ret == SOCKET_ERROR) &&
            (WSA_IO_PENDING != WSAGetLastError())) {
            WSACloseEvent(sndOverlapped.hEvent);
            throw SocketException("send failed with error: " + std::to_string(WSAGetLastError()));
        }

        DWORD rc = WSAWaitForMultipleEvents(1, &sndOverlapped.hEvent, TRUE, INFINITE,
                                            TRUE);
        if (rc == WSA_WAIT_FAILED) {
            WSACloseEvent(sndOverlapped.hEvent);
            throw SocketException("WSAWaitForMultipleEvents failed with error: " + std::to_string(WSAGetLastError()));
        }
        ret = WSAGetOverlappedResult(_socket, &sndOverlapped, &numberOfBytesSnd,
                                     FALSE, &flag);
        if (ret == FALSE) {

            WSACloseEvent(sndOverlapped.hEvent);
            throw SocketException("WSAgetOverlappedResult failed with error: " + std::to_string(WSAGetLastError()));
        }

        writeBuffer->second.first.updatePosition(numberOfBytesSnd);

        WSACloseEvent(sndOverlapped.hEvent);

    }

    void SocketWindowsUDP::close() {
        if (_socket != INVALID_SOCKET) {
            closesocket(_socket);
            _socket = INVALID_SOCKET;
        }
    }

}