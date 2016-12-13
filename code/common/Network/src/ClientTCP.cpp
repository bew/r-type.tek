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

    ClientTCP::ClientTCP() : _socket()
    {
    }

    ClientTCP::ClientTCP(Socket_t socket) : _socket(socket)
    {

    }

    ClientTCP::~ClientTCP()
    {
        if (!isClose())
            _selector.unmonitor(_socket.getSocket(), NetworkSelect::READ);

        _socket.close();
    }

    void ClientTCP::close()
    {
        _selector.unmonitor(_socket.getSocket(), NetworkSelect::READ);

        _socket.close();
    }

    void ClientTCP::connect(const SockAddr &hostInfos)
    {
        _socket.connect(hostInfos);
        _selector.monitor(_socket.getSocket(), NetworkSelect::READ);
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
                if ((msg = _writeBuffer.get()) != "")
                {
                    msg += CR;
                    msg += LF;
                    int nbBytesSend = _socket.send(msg);
                    _writeBuffer.updatePosition(static_cast<size_t>(nbBytesSend));

                    if (_writeBuffer.get() == "")
                        _selector.unmonitor(_socket.getSocket(), NetworkSelect::WRITE);
                }
            }
        }
        catch (SocketException &e)
        {
            std::cerr << e.what() << std::endl;
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
}