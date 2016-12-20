/**
 * @file NetworkSelect.hh
 * @author Tookie
 * @brief encapsulation of select system call
 */

#pragma once

#ifdef __linux__
#include <sys/select.h>
#elif defined _WIN32

#include <winsock2.h>

#endif

#include "ASocket.hh"

/**
 * namespace that contains all network abstraction
 */
namespace network {

    /**
     * Representation of select system call encapsulation
     */
    class NetworkSelect {
    public:

        /**
         * enum to know what fd set
         */
        enum SelectType {
            READ = 0,
            WRITE
        };

        /**
         * init all fd_set membres
         */
        NetworkSelect();

        /**
         * test if the readfd is monitored
         *
         * @return true if it's readable else false
         *
         * @param sockFd represent the socket that will be tested
         */
        bool isReadable(Socket_t sockFd) const;

        /**
         * test if the writefd is monitored
         *
         * @return true if it's readable else false
         *
         * @param sockFd represent the socket that will be tested
         */
        bool isWritable(Socket_t sockFd) const;

        /**
         * monitor socket's fd in read or write mode according to the type
         *
         * @param sockFd socket that will be monitor
         *
         * @param type READ or WRITE
         *
         * @throw SocketException if socket is invalid
         */
        void monitor(Socket_t sockFd, SelectType type);

        /**
         * unmonitor socket's fd in read or write mode according to the type
         *
         * @param sockFd socket that will be unmonitor
         *
         * @param type READ or WRITE
         *
         * @throw SocketException if socket is invalid
         */
        void unmonitor(Socket_t sockFd, SelectType type);

        /**
         * call select system call
         *
         * @param timer struct that will be pass to select
         *
         * @throw SocketException if socket is invalid
         */
        void select(struct timeval *timer);

    private:
        /**
         *  represent set of read fd
         */
        fd_set _readfds;

        /**
         *  represent set of write fd
         */
        fd_set _writefds;

        /**
         * represent set of read fd that will be pass to select
         */
        fd_set _readfds_result;

        /**
         * represent set of write fd that will be pass to select
         */
        fd_set _writefds_result;
    };

}