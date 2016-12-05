/**
 * @file SocketWindowsUDP.cpp
 * @author Tookie
 * @brief UDP socket encapsulation for windows
 */

#include <cstring>
#include <stdio.h>
#include <iostream>
#include "../include/SocketWindowsUDP.h"
#include "../include/SocketException.hh"

namespace network
{

    SocketWindowsUDP::SocketWindowsUDP(const unsigned short port) : ASocketUDP(port)
    {
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

    SocketWindowsUDP::~SocketWindowsUDP()
    {
        close();
        WSACleanup();
    }

    void SocketWindowsUDP::bind()
    {
        int ret = ::bind(_socket, reinterpret_cast<SOCKADDR *>(&_from), sizeof(_from));
        if (ret == SOCKET_ERROR)
            throw SocketException("bind failed with error: " + std::to_string(WSAGetLastError()));
        _selector.monitor(this, NetworkSelect::READ);
    }

    void SocketWindowsUDP::recv()
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
        int fromSize = sizeof(_from);
        while (buffer.buf[0] == 0)
        {
            flag = 0;
            int ret = WSARecvFrom(_socket, &buffer, 1, &numberOfBytesRecv, &flag, reinterpret_cast<sockaddr *>(&_from),
                                  &fromSize,
                                  &recvOverlapped,
                                  nullptr);
            if (((ret == SOCKET_ERROR) && (WSA_IO_PENDING != WSAGetLastError())))
            {
                WSACloseEvent(recvOverlapped.hEvent);
                throw SocketException("recv from failed with error: " + std::to_string(WSAGetLastError()));
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

    void SocketWindowsUDP::send(std::string &msg)
    {
        WSABUF buffer;

        buffer.buf = const_cast<char *>(msg.c_str());
        buffer.len = static_cast<u_long >(msg.length());

        WSAOVERLAPPED sndOverlapped;
        DWORD flag;
        int fromSize = sizeof(_from);
        DWORD numberOfBytesSnd = 0;

        flag = 0;

        sndOverlapped.hEvent = WSACreateEvent();
        if (sndOverlapped.hEvent == nullptr)
        {
            throw SocketException("WSACreateEvent failed: " + std::to_string(WSAGetLastError()));
        }

        int ret = WSASendTo(_socket,
                            &buffer,
                            1,
                            &numberOfBytesSnd,
                            flag,
                            reinterpret_cast<SOCKADDR *>(&_from),
                            fromSize,
                            &sndOverlapped,
                            nullptr);

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

    void SocketWindowsUDP::close()
    {
        if (_socket != INVALID_SOCKET)
        {
            closesocket(_socket);
            _socket = INVALID_SOCKET;
        }
    }

}