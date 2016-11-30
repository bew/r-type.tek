/**
 * @file SocketException.cpp
 * @author Tookie
 * @brief encapsulation of select system call
 */


#include "../include/SocketException.hh"

SocketException::SocketException(const std::string& error) throw():
        _msg(error)
{

}

const char* SocketException::what() const throw()
{
    return _msg.c_str();
}