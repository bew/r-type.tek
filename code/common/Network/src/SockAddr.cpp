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
        struct hostent *host;
        const char *ip;

        _addr.sin_family = AF_INET;
        if ((host = gethostbyname(addr.c_str())))
        {
            struct in_addr **addr_list = reinterpret_cast<struct in_addr **>(host->h_addr_list);
            ip = inet_ntoa(*addr_list[0]);
        }
        else
            ip = addr.c_str();

        inet_pton(AF_INET, ip, &(_addr.sin_addr));
        if (port > 0)
            _addr.sin_port = htons(port);
        else
            _addr.sin_port = port;
    }

    SockAddr::SockAddr(unsigned short port)
    {
        _addr.sin_family = AF_INET;
        _addr.sin_addr.s_addr = INADDR_ANY;
        _addr.sin_port = htons(port);
    }

    sockaddr_in& SockAddr::getAddr()
    {
        return _addr;
    }

    const sockaddr_in& SockAddr::getAddr() const
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

    unsigned short SockAddr::getPort() const
    {
        return ntohs(_addr.sin_port);
    }

}