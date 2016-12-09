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

    SocketWindowsTCP::SocketWindowsTCP(unsigned short port) : ASocketTCP(port)
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

    SocketWindowsTCP::~SocketWindowsTCP()
    {
        close();
        WSACleanup();
    }

    void SocketWindowsTCP::bind()
    {
        if (::bind(_socket, reinterpret_cast<SOCKADDR *>(&_from), sizeof(_from)) == SOCKET_ERROR)
            throw SocketException("bind failed with error: " + std::to_string(WSAGetLastError()));

    }

    void SocketWindowsTCP::listen()
    {
        if (::listen(_socket, SOMAXCONN) == SOCKET_ERROR)
            throw SocketException("Listen failed with error: " + std::to_string(WSAGetLastError()));
    }

    void SocketWindowsTCP::accept()
    {
        sockaddr clientInfos;
        int clientInfosSize = sizeof(sockaddr);
        if ((_socket = WSAAccept(_socket, &clientInfos, &clientInfosSize, nullptr, 0)) == SOCKET_ERROR)
            throw SocketException("Accept failed with error " + std::to_string(WSAGetLastError()));
        _selector.monitor(this, NetworkSelect::READ);
    }

    void SocketWindowsTCP::connect()
    {
        _from.setAddr(SERVER_ADDR);
        sockaddr_in from = _from.getAddr();

        int ret = ::WSAConnect(_socket,
                               reinterpret_cast<SOCKADDR *>(&from),
                               sizeof(_from.getAddr()),
                               nullptr,
                               nullptr,
                               nullptr,
                               nullptr);

        if (ret == SOCKET_ERROR)
            throw SocketException("Connect failed with error " + std::to_string(WSAGetLastError()));
    }

    void SocketWindowsTCP::close()
    {
        if (_socket != INVALID_SOCKET)
        {
            closesocket(_socket);
            _socket = INVALID_SOCKET;
        }

    }

    void SocketWindowsTCP::recv()
    {
        char bufTmp[BUFFER_SIZE];
        DWORD flag;
        DWORD numberOfBytesRecv = 0;
        WSAOVERLAPPED recvOverlapped;

        WSABUF buffer;

        std::memset(bufTmp, 0, BUFFER_SIZE);
        buffer.len = BUFFER_SIZE;
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

        std::string msg(buffer.buf, numberOfBytesRecv);

        msg += CR;
        _readBuffer.fill(msg);
    }

    void SocketWindowsTCP::send(const std::string &msg)
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

        _writeBuffer.updatePosition(numberOfBytesSnd);

        WSACloseEvent(sndOverlapped.hEvent);
    }

}
