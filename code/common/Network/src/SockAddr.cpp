/**
 * @file SockAddr.cpp
 * @author Tookie
 * @brief implemation of  sockaddr_in encapsulation
 */

#include "SockAddr.hh"

namespace network
{

    SockAddr::SockAddr(unsigned short port, const std::string &addr)
    {
        _addr.sin_family = AF_INET;
        inet_pton(AF_INET, addr.c_str(), &(_addr.sin_addr));
        _addr.sin_port = htons(port);
    }

    SockAddr::SockAddr(unsigned short port)
    {
        _addr.sin_family = AF_INET;
        _addr.sin_addr.s_addr = INADDR_ANY;
        _addr.sin_port = htons(port);
    }

    sockaddr_in SockAddr::getAddr() const
    {
        return _addr;
    }

    void SockAddr::setIPAddr(const std::string &addr)
    {
        inet_pton(AF_INET, addr.c_str(), &(_addr.sin_addr));
    }

    void SockAddr::setAddr(const sockaddr_in &addr)
    {
        _addr = addr;
    }

    bool SockAddr::operator==(const SockAddr &rhs) const
    {
        return (_addr.sin_addr.s_addr == rhs._addr.sin_addr.s_addr) && (_addr.sin_port == rhs._addr.sin_port);
    }

    bool SockAddr::operator!=(const SockAddr &rhs) const
    {
        return (!((*this) == rhs));
    }
}