/**
 * @file ClientUDP.cpp
 * @author Tookie
 * @brief implementation of Client UDP
 */


#include <iostream>
#include "SocketException.hh"
#include "ClientUDP.hh"

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

    void ClientUDP::update(unsigned long ms)
    {
        try
        {
            struct timeval timer;
            timer.tv_sec = ms / 1000;
            timer.tv_usec = (ms - (timer.tv_sec * 1000)) * 1000;
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
                    msg += network::getMagic();
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
        if (msg.size() >= 8 && msg.substr(msg.length() - 8) == network::getMagic())
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