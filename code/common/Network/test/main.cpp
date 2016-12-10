//
// Created by Tookie on 07/12/2016.
//

#include "gtest/gtest.h"

#include "SocketException.hh"

#ifdef __linux__
#include "SocketLinuxTCP.h"
#include "SocketLinuxUDP.h"
#elif defined _WIN32

#include "SocketWindowsTCP.h"
#include "SocketWindowsUDP.h"

#endif

#include <thread>
#include <../test/mingw.thread.h>
#include <mutex>
#include <../test/mingw.mutex.h>
#include <queue>
#include <atomic>

class ATask {
protected:
    class LockGuard {
    public:
        LockGuard(std::mutex &mutex) : _mutex(mutex) {
            _mutex.lock();
        };

        ~LockGuard() {
            _mutex.unlock();
        };

        LockGuard(const LockGuard &) = delete;

        LockGuard &operator=(const LockGuard &) = delete;

    private:
        std::mutex &_mutex;
    };

public:
    ATask() : _thread(), _mutex(), _done(false) {};

    virtual ~ATask() {};

    ATask(const ATask &) = delete;

    ATask &operator=(const ATask &) = delete;

    void launch() {
        _thread = std::thread([this] { this->execLoop(); });
    };

    void detach() {
        _thread.detach();
    };

    void join() {
        _thread.join();
    };

    bool isDone() const {
        return _done;
    };

    virtual void execLoop() = 0;

protected:

    std::atomic_bool _done;
    std::thread _thread;
    std::mutex _mutex;
};

class Client : public ATask {
public:
    Client(unsigned short port) : ATask() {
        _socketClient = new network::SocketTCP(port);
    };

    ~Client() {
        _socketClient->close();
        delete _socketClient;
    };

    virtual void execLoop() {
        _socketClient->connect();

        std::string login = "login" + CR;

        _socketClient->add(login);

        _socketClient->update();

        _socketClient->update();

        std::string ok;

        ok = _socketClient->get();

        ASSERT_STREQ("OK", ok.c_str());
    };

private:
    network::ASocketTCP *_socketClient;
};

TEST(Network, SocketTcp) {
    try {
        std::cout << "yo" << std::endl;
        network::ASocketTCP *socketServer = new network::SocketTCP(26130);
        Client client(26130);

        socketServer->bind();

        socketServer->listen();

        client.launch();
        client.detach();

        socketServer->accept();

        std::string login;

        socketServer->update();
        login = socketServer->get();

        ASSERT_STREQ("login", login.c_str());
        std::string ok = "OK" + CR;

        socketServer->add(ok);
        socketServer->update();

        socketServer->close();
    }
    catch (network::SocketException &e) {
        std::cerr << e.what() << std::endl;
    }
}

int main(int ac, char **av) {
    ::testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
}