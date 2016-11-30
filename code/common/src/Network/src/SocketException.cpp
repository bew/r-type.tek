/**
 * @file SocketException.cpp
 * @author Tookie
 * @brief encapsulation of select system call
 */

#include "../include/SocketException.hh"

namespace network
{
    SocketException::SocketException(const std::string &error): std::runtime_error(error)
    {

    }

}