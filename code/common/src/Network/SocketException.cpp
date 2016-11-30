//
// Created by Tookie on 12/10/2016.
//

#include "Network/SocketException.h"

SocketException::SocketException(const std::string& error) throw():
        _msg(error)
{

}

const char* SocketException::what() const throw()
{
    return _msg.c_str();
}