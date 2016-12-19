/**
 * @file ClientUDP.cpp
 * @author Tookie
 * @brief implementation of Client UDP
 */


#include <iostream>
#include "SocketException.hh"
#include "ClientUDP.hpp"

namespace network
{
    ClientUDP::ClientUDP(const std::string &serverAddr, unsigned short port) : _addr(port, serverAddr)
    {
        _selector.monitor(_socket.getSocket(), NetworkSelect::READ);
    }

    ClientUDP::ClientUDP(const SockAddr &addr) : _addr(addr)
    {
        _selector.monitor(_socket.getSocket(), NetworkSelect::READ);
    }

    ClientUDP::~ClientUDP()
    {
        close();
    }

    void ClientUDP::update()
    {
        try
        {
            struct timeval timer;
            timer.tv_sec = 1;
            timer.tv_usec = 0;
            _selector.select(&timer);
            if (_selector.isReadable(_socket.getSocket()))
            {
                SockAddr from(0, "");
                std::string msg = _socket.recv(from);
                if (from != _addr)
                    throw SocketException("Client read from unknown host");
                _readBuffer.fill(msg);

            }
            if (_selector.isWritable(_socket.getSocket()))
            {
                std::string msg;
                if (!(msg = _writeBuffer.get()).empty())
                {
                    msg += network::CR;
                    msg += network::LF;
                    size_t nbBytesSend = _socket.send(_addr, msg);
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

    void ClientUDP::addMessage(const std::string &msg)
    {
        _writeBuffer.fill(msg);
        if (*(--msg.end()) == network::CR || *(--msg.end()) == network::LF)
            _selector.monitor(_socket.getSocket(), NetworkSelect::WRITE);
    }

    SockAddr &ClientUDP::getAddr()
    {
        return _addr;
    }

    bool ClientUDP::isClose() const
    {
        return (_socket.getSocket() == -1);
    }

    void ClientUDP::close()
    {
        if (!isClose())
        {
            _selector.unmonitor(_socket.getSocket(), NetworkSelect::READ);
            _selector.unmonitor(_socket.getSocket(), NetworkSelect::WRITE);
            _socket.close();
        }
    }

}