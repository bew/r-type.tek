/**
 * @file SocketException.hh
 * @author Tookie
 * @brief encapsulation of select system call
 */

#pragma once

#include <exception>
#include <string>

class SocketException: public std::exception {
public:
    SocketException(const std::string&) throw();

    virtual const char* what() const throw();

    virtual ~SocketException() throw() {}


private:
    std::string _msg;

};