/**
 * @file ATask.cpp
 * @author Tookie
 * @brief abstraction of thread and mutex encapsulation
 */

#include "ATask.hh"

namespace concurrency
{
    ATask::LockGuard::LockGuard(std::mutex &mutex) : _mutex(mutex)
    {
        _mutex.lock();
    }

    ATask::LockGuard::~LockGuard()
    {
        _mutex.unlock();
    }

    ATask::ATask() : _thread(), _mutex(), _done(false)
    {}

    void ATask::launch()
    {
        _thread = std::thread([this]
                              { this->execLoop(); });
    }

    void ATask::detach()
    {
        _thread.detach();
    }

    void ATask::join()
    {
        _thread.join();
    }

    bool ATask::isDone() const
    {
        return _done;
    }

}
