//
// Created by Tookie on 12/10/2016.
//

#ifndef ABSTRACTIONSOCKET_SOCKETEXCEPTION_H
#define ABSTRACTIONSOCKET_SOCKETEXCEPTION_H


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


#endif //ABSTRACTIONSOCKET_SOCKETEXCEPTION_H
