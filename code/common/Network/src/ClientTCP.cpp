/**
 * @file ClientTCP.cpp
 * @author Tookie
 * @brief implementation of Client TCP class
 */


#include <iostream>
#include "ClientTCP.hpp"
#include "SocketException.hh"

namespace network
{

    ClientTCP::ClientTCP() : _socket(), _isConnected(false)
    {
    }

    ClientTCP::ClientTCP(Socket_t socket) : _socket(socket), _isConnected(true)
    {

    }

    ClientTCP::~ClientTCP()
    {
       close();
    }

    void ClientTCP::close()
    {
        if (!isClose())
        {
            _selector.unmonitor(_socket.getSocket(), NetworkSelect::READ);
            _selector.unmonitor(_socket.getSocket(), NetworkSelect::WRITE);
            _socket.close();
        }
    }

    void ClientTCP::connect(const SockAddr &hostInfos)
    {
        if (!_isConnected)
        {
            _socket.connect(hostInfos);
            _selector.monitor(_socket.getSocket(), NetworkSelect::READ);
            _isConnected = true;
        }
    }

    void ClientTCP::update()
    {
        if (isClose())
            return;
        try
        {
            struct timeval timer;
            timer.tv_sec = 1;
            timer.tv_usec = 0;
            _selector.select(&timer);
            if (_selector.isReadable(_socket.getSocket()))
            {
                std::string msg = _socket.recv();
                _readBuffer.fill(msg);
                if (isClose())
                    return;

            }
            if (_selector.isWritable(_socket.getSocket()))
            {
                std::string msg;
                if (!(msg = _writeBuffer.get()).empty())
                {
                    msg += CR;
                    msg += LF;
                    size_t nbBytesSend = _socket.send(msg);
                    _writeBuffer.updatePosition(nbBytesSend);

                    if (_writeBuffer.get().empty())
                        _selector.unmonitor(_socket.getSocket(), NetworkSelect::WRITE);
                }
            }
        }
        catch (SocketException &e)
        {
            throw e;
        }
    }

    void ClientTCP::addMessage(const std::string &msg)
    {
        _writeBuffer.fill(msg);
        if (*(--msg.end()) == CR || *(--msg.end()) == LF)
            _selector.monitor(_socket.getSocket(), NetworkSelect::WRITE);
    }

    SocketTCP &ClientTCP::getSocket()
    {
        return _socket;
    }

    bool ClientTCP::isClose() const
    {
        return (_socket.getSocket() == -1);
    }

    bool ClientTCP::isConnected() const
    {
        return _isConnected;
    }
}