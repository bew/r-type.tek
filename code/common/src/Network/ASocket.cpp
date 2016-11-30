//
// Created by Tookie on 12/10/2016.
//

#include <iostream>
#include "Network/ASocket.h"


ASocket::ASocket(const unsigned short port)
        : _port(port){
    _from.sin_family = AF_INET;
    _from.sin_addr.s_addr = INADDR_ANY;
    _from.sin_port = htons(_port);
}

void ASocket::update() {
    struct timeval timer;
    timer.tv_sec = 5;
    timer.tv_usec = 0;
    _selector.select(&timer);
    if (_selector.isReadable(this)) {
        std::cout << "readable" << std::endl;
        recv();
    }
    if (_selector.isWritable(this)) {
        std::string msg;
        if ((msg = _writeBuffer.get()) != "") {
            send(msg);
            _selector.unmonitor(this, NetworkSelect::WRITE);
        }
    }
}

std::string ASocket::get() {
    std::string msg = _readBuffer.get();
    _readBuffer.updatePosition(msg.length());
    return msg;
}

void ASocket::add(const std::string &msg) {
    _writeBuffer.fill(msg);
    _selector.monitor(this, NetworkSelect::WRITE);
}

Socket_t ASocket::getSocket() const {
    return _socket;
}