//
// Created by Tookie on 07/12/2016.
//

#include "gtest/gtest.h"

#include "SocketException.hh"
#include <thread>
#include <mutex>
#include <queue>
#include <atomic>

#ifdef __linux__

#include "SocketLinuxTCP.h"
#include "SocketLinuxUDP.h"

#elif defined _WIN32
#include <../test/mingw.thread.h>
#include <../test/mingw.mutex.h>
#include "SocketWindowsTCP.h"
#include "SocketWindowsUDP.h"

#endif

class ATask
{
protected:
    class LockGuard
    {
    public:
        LockGuard(std::mutex &mutex) : _mutex(mutex)
        {
            _mutex.lock();
        };

        ~LockGuard()
        {
            _mutex.unlock();
        };

        LockGuard(const LockGuard &) = delete;

        LockGuard &operator=(const LockGuard &) = delete;

    private:
        std::mutex &_mutex;
    };

public:
    ATask() : _thread(), _mutex(), _done(false)
    {};

    virtual ~ATask()
    {};

    ATask(const ATask &) = delete;

    ATask &operator=(const ATask &) = delete;

    void launch()
    {
        _thread = std::thread([this]
                              { this->execLoop(); });
    };

    void detach()
    {
        _thread.detach();
    };

    void join()
    {
        _thread.join();
    };

    bool isDone() const
    {
        return _done;
    };

    virtual void execLoop() = 0;

protected:

    std::atomic_bool _done;
    std::thread _thread;
    std::mutex _mutex;
};

class Client : public ATask
{
public:
    Client(unsigned short port) : ATask()
    {
        _socketClient = new network::SocketTCP(port);
    };

    ~Client()
    {
        _socketClient->close();
        delete _socketClient;
    };

    virtual void execLoop()
    {

        _socketClient->connect();

        std::string login("login");
        login += CR;

        _socketClient->add(_socketClient->getSocket(), login);

        _socketClient->update();

        std::string ok = "";

        while ((ok = _socketClient->get(_socketClient->getSocket())) == "")
            _socketClient->update();

        ASSERT_STREQ("OK", ok.c_str());
    };

private:
    network::ASocketTCP *_socketClient;
};

TEST(Network, SingleSocketTcp)
{
    try
    {
        network::ASocketTCP *socketServer = new network::SocketTCP(26121);
        Client client(26121);

        socketServer->bind();

        socketServer->listen();

        client.launch();
        client.detach();

        socketServer->accept();

        std::string login = "";

        while ((login = socketServer->get(socketServer->getConnections().at(0))) == "")
            socketServer->update();

        std::string ok("OK");
        ok += CR;

        socketServer->add(socketServer->getConnections().at(0), ok);
        socketServer->update();

        socketServer->close();
        delete (socketServer);
    }
    catch (network::SocketException &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

TEST(Network, Singlepd)
{
    try
    {
        network::ASocketTCP *socketServer = new network::SocketTCP(26129);
        Client client(26129);

        socketServer->bind();

        socketServer->listen();

        client.launch();
        client.detach();

        socketServer->accept();

        std::string login = "";

        while ((login = socketServer->get(socketServer->getConnections().at(0))) == "")
            socketServer->update();

        std::string ok("OK");
        ok += CR;

        socketServer->add(socketServer->getConnections().at(0), ok);
        socketServer->update();

        socketServer->close();
        delete (socketServer);
    }
    catch (network::SocketException &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

/**
TEST(Network, MultipleSocketTcp)
{
    try
    {
        network::ASocketTCP *socketServer = new network::SocketTCP(26120);

        Client client0(26120);
        Client client1(26120);
        Client client2(26120);
        Client client3(26120);

        socketServer->bind();

        socketServer->listen();

        client0.launch();
        client0.detach();

        socketServer->accept();

        std::string login = "";

        // Client 0

        while ((login = socketServer->get(socketServer->getConnections().at(0))) == "")
            socketServer->update();

        ASSERT_STREQ("login", login.c_str());
        std::string ok("OK");
        ok += CR;

        socketServer->add(socketServer->getConnections().at(0), ok);
        socketServer->update();

        client1.launch();
        client1.detach();

        socketServer->accept();

        //Client 1
        login = "";
        while ((login = socketServer->get(socketServer->getConnections().at(1))) == "")
            socketServer->update();

        ASSERT_STREQ("login", login.c_str());

        ok = "OK";
        ok += CR;

        socketServer->add(socketServer->getConnections().at(1), ok);
        socketServer->update();

        client2.launch();
        client2.detach();

        socketServer->accept();

        //Client 2
        login = "";
        while ((login = socketServer->get(socketServer->getConnections().at(2))) == "")
            socketServer->update();

        ASSERT_STREQ("login", login.c_str());

        ok = "OK";
        ok += CR;

        socketServer->add(socketServer->getConnections().at(2), ok);
        socketServer->update();

        //Client 3
        client3.launch();
        client3.detach();

        socketServer->accept();

        login = "";
        while ((login = socketServer->get(socketServer->getConnections().at(3))) == "")
            socketServer->update();

        ASSERT_STREQ("login", login.c_str());

        ok = "OK";
        ok += CR;

        socketServer->add(socketServer->getConnections().at(3), ok);
        socketServer->update();

        socketServer->close();

        delete (socketServer);
    }
    catch (network::SocketException &e)
    {
        std::cerr << e.what() << std::endl;
    }
}
 */

int main(int ac, char **av)
{
    ::testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
}