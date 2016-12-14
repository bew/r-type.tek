//
// Created by tookie on 12/14/16.
//

#pragma once

#include <thread>
#include <mutex>
#include <atomic>
#include "SockAddr.hh"
#include "ClientUDP.hpp"

class ATask
{
protected:
    class LockGuard
    {
    public:
        LockGuard(std::mutex &mutex);

        ~LockGuard();

        LockGuard(const LockGuard &) = delete;

        LockGuard &operator=(const LockGuard &) = delete;

    private:
        std::mutex &_mutex;
    };

public:
    ATask();

    virtual ~ATask()
    {};

    ATask(const ATask &) = delete;

    ATask &operator=(const ATask &) = delete;

    void launch();

    void detach();

    void join();

    bool isDone() const;

    virtual void execLoop() = 0;

protected:

    std::atomic_bool _done;
    std::thread _thread;
    std::mutex _mutex;
};

class ClientUDP : public ATask
{
public:
    ClientUDP(const network::SockAddr &serverInfos);

    ~ClientUDP()
    {};

    virtual void execLoop();

private:
    network::ClientUDP _client;
};
