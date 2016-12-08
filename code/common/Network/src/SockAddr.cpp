/**
 * @file SockAddr.cpp
 * @author Tookie
 * @brief encapsulation of sockaddr_in type
 */

#include "SockAddr.hh"

namespace network {


    SockAddr::SockAddr(unsigned short port, const std::string &addr)
    {
        _addr.sin_family = AF_INET;
        _addr.sin_addr.s_addr = inet_addr(addr.c_str());
        _addr.sin_port = htons(port);
    }

    SockAddr::SockAddr(unsigned short port)
    {
        _addr.sin_family = AF_INET;
        _addr.sin_addr.s_addr = INADDR_ANY;
        _addr.sin_port = htons(port);
    }

    sockaddr_in &SockAddr::getAddr()
    {
        return _addr;
    }

    void SockAddr::setAddr(const std::string &addr) {
        _addr.sin_addr.s_addr = inet_addr(addr.c_str());
    }

}