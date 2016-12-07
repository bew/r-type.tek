/**
 * @file SocketException.hh
 * @author Tookie
 * @brief class for socket exception
 */

#pragma once

#include <stdexcept>

/**
 * namespace that contains all network abstraction
 */
namespace network {

    /**
     * Representation of socket exception
     */
    class SocketException : public std::runtime_error {
    public:

        /**
         * ctor of SocketException
         *
         * @param error: message of the exception
         */
        SocketException(const std::string &error);
    };

}