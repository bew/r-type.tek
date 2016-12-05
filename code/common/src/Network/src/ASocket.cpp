/**
 * @file ASocket.cpp
 * @author Tookie
 * @brief abstraction socket implentation
 */

#include "../include/ASocket.hh"

namespace network
{

    ASocket::ASocket(unsigned short port)
            : _port(port)
    {
        _from.sin_family = AF_INET;
        _from.sin_addr.s_addr = INADDR_ANY;
        _from.sin_port = htons(_port);
    }

    void ASocket::update()
    {
        struct timeval timer;
        timer.tv_sec = 1;
        timer.tv_usec = 0;
        _selector.select(&timer);
        if (_selector.isReadable(this))
        {
            recv();
        }
        if (_selector.isWritable(this))
        {
            std::string msg;
            if ((msg = _writeBuffer.get()) != "")
            {
                send(msg);
                if (get() == "")
                    _selector.unmonitor(this, NetworkSelect::WRITE);
            }
        }
    }

    std::string ASocket::get()
    {
        std::string msg = _readBuffer.get();
        _readBuffer.updatePosition(msg.length());
        return msg;
    }

    void ASocket::add(const std::string &msg)
    {
        _writeBuffer.fill(msg);
        if (*(--msg.end()) == CR || *(--msg.end()) == LF)
        {
            _selector.monitor(this, NetworkSelect::WRITE);
        }
    }

    Socket_t ASocket::getSocket() const
    {
        return _socket;
    }

}