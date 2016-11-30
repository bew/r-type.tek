//
// Created by Tookie on 12/10/2016.
//

#ifndef ABSTRACTIONSOCKET_ISOCKET_H
#define ABSTRACTIONSOCKET_ISOCKET_H

#include <string>

#include "Network/NetworkBuffer.h"
#include "Network/NetworkSelect.h"

#ifdef __linux__
#define Socket_t int

#include <netinet/in.h>
#elif defined _WIN32
#define Socket_t long long
#include<winsock2.h>
#endif

class ASocket
{
public:
    ASocket(const unsigned short);

    virtual void bind() = 0;

    virtual void update();

    virtual std::string get();

    virtual void add(const std::string &);

    virtual void close() = 0;

    Socket_t getSocket() const;

protected:
    virtual void recv() = 0;

    virtual void send(std::string &) = 0;

    Socket_t _socket;
    NetworkBuffer _readBuffer;
    NetworkBuffer _writeBuffer;
    NetworkSelect _selector;
    const unsigned short _port;
    sockaddr_in _from;
};


#endif //ABSTRACTIONSOCKET_ISOCKET_H
