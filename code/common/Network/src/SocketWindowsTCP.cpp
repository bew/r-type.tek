/**
 * @file SocketWindowsTCP.cpp
 * @author Tookie
 * @brief TCP socket encapsulation for windows
 */

#include <iostream>
#include <cstring>
#include <winsock2.h>
#include "SocketWindowsTCP.h"
#include "SocketException.hh"

namespace network
{

    SocketWindowsTCP::SocketWindowsTCP() : ASocketTCP()
    {
        WSADATA wsd;

        if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
            throw SocketException("WSAStartup failed with error: " + std::to_string(WSAGetLastError()));

        _socket = WSASocket(AF_INET,
                            SOCK_STREAM,
                            IPPROTO_TCP,
                            nullptr,
                            0,
                            WSA_FLAG_OVERLAPPED);

        if (_socket == INVALID_SOCKET)
            throw SocketException("WSA Socket failed with error: " + std::to_string(WSAGetLastError()));
    }

    SocketWindowsTCP::SocketWindowsTCP(Socket_t socket): ASocketTCP(socket)
    {}

    SocketWindowsTCP::~SocketWindowsTCP()
    {
        close();
        WSACleanup();
    }

    void SocketWindowsTCP::bind(SockAddr& hostInfos)
    {
        sockaddr_in addr = hostInfos.getAddr();
        if (::bind(_socket, reinterpret_cast<SOCKADDR *>(&addr), sizeof(addr)) == SOCKET_ERROR)
            throw SocketException("bind failed with error: " + std::to_string(WSAGetLastError()));

    }

    void SocketWindowsTCP::listen()
    {
        if (::listen(_socket, SOMAXCONN) == SOCKET_ERROR)
            throw SocketException("Listen failed with error: " + std::to_string(WSAGetLastError()));
    }

    Socket_t SocketWindowsTCP::accept()
    {
        sockaddr clientInfos;
        int clientInfosSize = sizeof(sockaddr);
        Socket_t newConnection;
        if ((newConnection = WSAAccept(_socket, &clientInfos, &clientInfosSize, nullptr, 0)) == SOCKET_ERROR)
            throw SocketException("Accept failed with error " + std::to_string(WSAGetLastError()));
        return newConnection;
    }

    void SocketWindowsTCP::connect(SockAddr& hostInfos)
    {
        sockaddr_in from = hostInfos.getAddr();

        if (::WSAConnect(_socket, reinterpret_cast<SOCKADDR *>(&from), sizeof(from), nullptr, nullptr, nullptr, nullptr) == SOCKET_ERROR)
            throw SocketException("Connect failed with error " + std::to_string(WSAGetLastError()));
    }

    void SocketWindowsTCP::close()
    {
        if (_socket != -1)
        {
            closesocket(_socket);
            _socket = -1;
        }
    }

    std::string SocketWindowsTCP::recv()
    {
        char bufTmp[network::BUFFER_SIZE];
        DWORD flag;
        DWORD numberOfBytesRecv = 0;
        WSAOVERLAPPED recvOverlapped;

        WSABUF buffer;

        std::memset(bufTmp, 0, network::BUFFER_SIZE);
        buffer.len = network::BUFFER_SIZE;
        buffer.buf = bufTmp;
        recvOverlapped.hEvent = WSACreateEvent();
        if (recvOverlapped.hEvent == nullptr)
            throw SocketException("WSACreateEvent failed: " + std::to_string(WSAGetLastError()));
        while (buffer.buf[0] == 0)
        {
            flag = 0;
            int ret = WSARecv(_socket, &buffer, 1, &numberOfBytesRecv, &flag, &recvOverlapped, nullptr);
            if (((ret == SOCKET_ERROR) && (WSA_IO_PENDING != WSAGetLastError())))
            {
                WSACloseEvent(recvOverlapped.hEvent);
                throw SocketException("recv failed with error: " + std::to_string(WSAGetLastError()));
            }
            DWORD rc = WSAWaitForMultipleEvents(1, &recvOverlapped.hEvent, TRUE, INFINITE, TRUE);
            if (rc == WSA_WAIT_FAILED)
            {
                WSACloseEvent(recvOverlapped.hEvent);
                throw SocketException(
                        "Wsa wait for multiple events failed with error: " + std::to_string(WSAGetLastError()));
            }

            ret = WSAGetOverlappedResult(_socket, &recvOverlapped, &numberOfBytesRecv, FALSE, &flag);
            if (ret == FALSE)
            {
                WSACloseEvent(recvOverlapped.hEvent);
                throw SocketException(
                        "Wsa get overlapped result events failed with error: " + std::to_string(WSAGetLastError()));
            }
            WSAResetEvent(recvOverlapped.hEvent);
        }
        WSACloseEvent(recvOverlapped.hEvent);
        if (numberOfBytesRecv == 0)
            close();
        return std::string(buffer.buf, numberOfBytesRecv);
    }

    size_t SocketWindowsTCP::send(const std::string &msg) const
    {
        WSABUF buffer;

        buffer.buf = const_cast<char *>(msg.c_str());
        buffer.len = static_cast<u_long >(msg.length());

        WSAOVERLAPPED sndOverlapped;
        DWORD flag;
        DWORD numberOfBytesSnd = 0;

        flag = 0;

        sndOverlapped.hEvent = WSACreateEvent();
        if (sndOverlapped.hEvent == nullptr)
            throw SocketException("WSACreateEvent failed: " + std::to_string(WSAGetLastError()));

        int ret = WSASend(_socket, &buffer, 1, &numberOfBytesSnd, flag, &sndOverlapped, nullptr);

        if ((ret == SOCKET_ERROR) &&
            (WSA_IO_PENDING != WSAGetLastError()))
        {
            WSACloseEvent(sndOverlapped.hEvent);
            throw SocketException("send failed with error: " + std::to_string(WSAGetLastError()));
        }

        DWORD rc = WSAWaitForMultipleEvents(1, &sndOverlapped.hEvent, TRUE, INFINITE,
                                            TRUE);
        if (rc == WSA_WAIT_FAILED)
        {
            WSACloseEvent(sndOverlapped.hEvent);
            throw SocketException("WSAWaitForMultipleEvents failed with error: " + std::to_string(WSAGetLastError()));
        }

        ret = WSAGetOverlappedResult(_socket, &sndOverlapped, &numberOfBytesSnd,
                                     FALSE, &flag);
        if (ret == FALSE)
        {

            WSACloseEvent(sndOverlapped.hEvent);
            throw SocketException("WSAgetOverlappedResult failed with error: " + std::to_string(WSAGetLastError()));
        }

        WSACloseEvent(sndOverlapped.hEvent);

        return numberOfBytesSnd;
    }

}
