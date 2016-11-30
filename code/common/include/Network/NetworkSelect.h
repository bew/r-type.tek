//
// Created by Tookie on 22/11/2016.
//

#ifndef ABSTRACTIONSOCKET_NETWORKSELECT_H
#define ABSTRACTIONSOCKET_NETWORKSELECT_H

#ifdef __linux__
    #include <sys/select.h>
#elif defined _WIN32
    #include <winsock2.h>
#endif

class NetworkSelect;
class ASocket;

class NetworkSelect {
public:

    enum SelectType {
        READ = 0,
        WRITE
    };

    NetworkSelect();

    bool isReadable(const ASocket *) const;

    bool isWritable(const ASocket *) const;

    void monitor(const ASocket *, SelectType);

    void unmonitor(const ASocket *, SelectType);

    void select(struct timeval *);

private:
    fd_set _readfds;
    fd_set _writefds;
    fd_set _readfds_result;
    fd_set _writefds_result;
};


#endif //ABSTRACTIONSOCKET_NETWORKSELECT_H
