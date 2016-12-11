/**
 * @file ASocketTCP.cpp
 * @author Tookie
 * @brief abstraction of TCP socket
 */

#include "ASocketTCP.hh"

namespace network
{

    ASocketTCP::ASocketTCP(unsigned short port) : ASocket(port),
                                                  _from(_port)
    {

    }

    void ASocketTCP::update()
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
                if (_writeBuffer.get() == "")
                    _selector.unmonitor(this, NetworkSelect::WRITE);
            }
        }
    }

    std::string ASocketTCP::get()
    {
        std::string msg = _readBuffer.get();
        _readBuffer.updatePosition(msg.length());
        return msg;
    }

    void ASocketTCP::add(const std::string &msg)
    {
        _writeBuffer.fill(msg);
        if (*(--msg.end()) == CR || *(--msg.end()) == LF)
        {
            _selector.monitor(this, NetworkSelect::WRITE);
        }
    }

}