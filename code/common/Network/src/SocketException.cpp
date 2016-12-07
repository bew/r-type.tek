/**
 * @file SocketException.cpp
 * @author Tookie
 * @brief class for socket exception
 */

#include "../include/SocketException.hh"

namespace network {

    SocketException::SocketException(const std::string &error) : std::runtime_error(error) {
    }

}