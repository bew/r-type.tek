//
// Created by Tookie on 22/11/2016.
//

#include <iostream>
#include "Network/NetworkBuffer.h"

NetworkBuffer::NetworkBuffer() {
    initBuffer();
    _readPosition = 0;
    _writePosition = 0;
}

NetworkBuffer::~NetworkBuffer() {

}

void NetworkBuffer::fill(const std::string &msg) {
    std::cout << "fill" << msg << std::endl;
    for (char c : msg) {
        _buffer[_writePosition] = c;
        ++_writePosition;
        if (_writePosition == BUFFER_SIZE)
            _writePosition = 0;
    }
}

void NetworkBuffer::updatePosition(size_t length) {
    size_t i = 0;

    std::cout << "update position: " << length << " " << _readPosition << std::endl;
    while (i < length) {
        ++_readPosition;
        if (_readPosition == BUFFER_SIZE)
            _readPosition = 0;
        i++;
    }
    if (_buffer[_readPosition] == CR || _buffer[_readPosition] == LF || _buffer[_readPosition] == 0) {
        std::cout << "update rec : " << _readPosition << std::endl;
        _buffer[_readPosition] = -1;
        updatePosition(1);
    }
    std::cout << "updated position: " << length << " " << _readPosition << std::endl;
}

std::string NetworkBuffer::get() {
    int i = 0;

    size_t readPosition = _readPosition;
    while (i < BUFFER_SIZE) {
        if (_buffer[readPosition] == CR || _buffer[readPosition] == LF) {
            std::cout << "got message: " << readPosition << std::endl;
            std::string msg;
            size_t beg = _readPosition;
            while (readPosition != beg) {
                msg += _buffer[beg];
                beg++;
                if (beg == BUFFER_SIZE)
                    beg = 0;
            }
            std::cout << "got: " << msg << std::endl;
            return msg;
        }
        ++readPosition;
        if (readPosition == BUFFER_SIZE)
            readPosition = 0;
        ++i;
    }
    std::cout << "nothing to get" << std::endl;
    return "";
}

void NetworkBuffer::initBuffer() {
    for (int i = 0; i < BUFFER_SIZE; i++) {
        _buffer[i] = -1;
    }
}
