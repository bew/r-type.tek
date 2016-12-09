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

    const sockaddr_in& SockAddr::getAddr() const
    {
        return _addr;
    }

    void SockAddr::setAddr(const std::string &addr) {
        _addr.sin_addr.s_addr = inet_addr(addr.c_str());
    }

    bool SockAddr::operator<(const SockAddr& rhs) const
    {
        std::string thisId(std::to_string(_addr.sin_addr.s_addr) + std::to_string(_addr.sin_port));
        std::string rhsId(std::to_string(rhs._addr.sin_addr.s_addr) + std::to_string(rhs._addr.sin_port));
        return thisId < rhsId;
    }
}