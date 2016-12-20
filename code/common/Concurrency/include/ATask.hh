/**
 * @file ATask.hh
 * @author Tookie
 * @brief abstraction of thread and mutex encapsulation
 */

#pragma once

#include <thread>
#include <mutex>
#include <atomic>

/**
 * namespace that contains all concurrency encapsulation
 */
namespace concurrency
{

    /**
     * class that represents one thread and one mutex
     */
    class ATask
    {
    protected:

        /**
         * class that encapsulates mutex
         */
        class LockGuard
        {
        public:
            /**
             * Constructor of LockGuard
             * @param mutex mutex to lock
             */
            LockGuard(std::mutex &mutex);

            /**
             * Destructor of LockGuard
             */
            ~LockGuard();

            LockGuard(const LockGuard &) = delete;

            LockGuard &operator=(const LockGuard &) = delete;

        private:
            /**
             * represents one mutex
             */
            std::mutex &_mutex;
        };

    public:
        /**
         * Constructor of ATask
         */
        ATask();

        /**
         * Destructor of ATask
         */
        virtual ~ATask()
        {};

        ATask(const ATask &) = delete;

        ATask &operator=(const ATask &) = delete;

        /**
         * launch his thread and call execLoop
         */
        void launch();

        /**
         * detach the thread
         */
        void detach();

        /**
         * join the thread
         */
        void join();

        /**
         * getter for done attribute
         * @return boolean, true if thread has finished, else false
         */
        bool isDone() const;

        /**
         * function calls by launch method, his execution is in the thread attribute
         */
        virtual void execLoop() = 0;

    protected:

        /**
         * indicates if the thread has finished or not
         */
        std::atomic_bool _done;

        /**
         * represents one thread
         */
        std::thread _thread;

        /**
         * represents one mutex, use for create LockGuard
         */
        std::mutex _mutex;
    };

}