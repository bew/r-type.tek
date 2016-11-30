//
// Created by Tookie on 22/11/2016.
//

#ifndef ABSTRACTIONSOCKET_NETWORKBUFFER_H
#define ABSTRACTIONSOCKET_NETWORKBUFFER_H

#include <string>

#define BUFFER_SIZE (4096)
# define CR ('\r')
# define LF ('\n')

class NetworkBuffer {
public:
    NetworkBuffer();
    ~NetworkBuffer();

    void fill(const std::string& msg);
    void updatePosition(size_t);
    std::string get();
private:
    void initBuffer();

    char _buffer[BUFFER_SIZE];
    size_t _readPosition;
    size_t _writePosition;
};


#endif //ABSTRACTIONSOCKET_NETWORKBUFFER_H
