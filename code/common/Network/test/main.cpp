//
// Created by Tookie on 07/12/2016.
//

#include "gtest/gtest.h"

#include "SocketException.hh"
#include <thread>
#include <mutex>
#include <queue>
#include <atomic>
#include <ClientTCP.hpp>
#include <ServerTCP.hpp>
#include <cstdlib>
#include <ClientUDP.hpp>
#include <ServerUDP.hpp>

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

class ClientTCP : public ATask
{
public:
    ClientTCP(const network::SockAddr& serverInfos) : ATask(), _client(), _serverInfos(serverInfos)
    {
    };

    ~ClientTCP()
    {
    };

    virtual void execLoop()
    {

        _client.connect(_serverInfos);

        std::string login("login");
        login += CR;
        login += LF;

        _client.addMessage(login);

        _client.update();

        std::string ok = "";

        while ((ok = _client.getMessage()) == "")
            _client.update();

        ASSERT_STREQ("OK", ok.c_str());
    };

private:
    network::ClientTCP _client;
    network::SockAddr _serverInfos;
};

class ClientUDP : public ATask
{
public:
    ClientUDP(const network::SockAddr& serverInfos) : ATask(), _client(serverInfos)
    {
    };

    ~ClientUDP()
    {

    };

    virtual void execLoop()
    {

        std::string login("login");
        login += CR;
        login += LF;

        _client.addMessage(login);

        _client.update();

        std::string ok = "";

        while ((ok = _client.getMessage()) == "")
            _client.update();

        ASSERT_STREQ("OK", ok.c_str());
    };

private:
    network::ClientUDP _client;
};

TEST(Network, SingleClientUdp)
{

    try
    {
        std::srand(std::time(0)); // use current time as seed for random generator
        unsigned short random_variable = std::rand() % 65000 + 2500;

        network::SockAddr clienInfos(random_variable);

        network::SockAddr serverInfos(random_variable, "127.0.0.1");

        network::ServerUDP server;
        ClientUDP client(serverInfos);

        server.bind(clienInfos);

        client.launch();

        std::string login = "";

        while(server.getConnections().size() == 0)
            server.update();

        login = server.getMessage(server.getConnections().at(0));

        ASSERT_STREQ("login", login.c_str());

        std::string ok("OK");
        ok += CR;
        ok += LF;

        server.addMessage(server.getConnections().at(0), ok);
        server.update();

        client.join();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}


TEST(Network, TwoClientUdp)
{
    try
    {
        std::srand(std::time(0)); // use current time as seed for random generator
        unsigned short random_variable = std::rand() % 65000 + 2500;

        network::SockAddr clienInfos(random_variable);
        network::SockAddr serverInfos(random_variable, "127.0.0.1");

        network::ServerUDP server;

        ClientUDP client0(serverInfos);
        ClientUDP client1(serverInfos);

        server.bind(clienInfos);

        client0.launch();

        while (server.getConnections().size() == 0)
            server.update();

        std::string login = "";

        // Client 0

        login = server.getMessage(server.getConnections().at(0));

        ASSERT_STREQ("login", login.c_str());

        std::string ok("OK");
        ok += CR;
        ok += LF;

        server.addMessage(server.getConnections().at(0), ok);
        server.update();
        client0.join();

        client1.launch();

        while (server.getConnections().size() == 1)
            server.update();

        //Client 1
        login = "";
        login = server.getMessage(server.getConnections().at(1));

        ASSERT_STREQ("login", login.c_str());

        ok = "OK";
        ok += CR;
        ok += LF;

        server.addMessage(server.getConnections().at(1), ok);
        server.update();
        client1.join();
    }
    catch (network::SocketException &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

TEST(Network, FourClientUdp)
{
    try
    {
        std::srand(std::time(0)); // use current time as seed for random generator
        unsigned short random_variable = std::rand() % 65000 + 2500;

        network::SockAddr clienInfos(random_variable);
        network::SockAddr serverInfos(random_variable, "127.0.0.1");

        network::ServerUDP server;

        ClientUDP client0(serverInfos);
        ClientUDP client1(serverInfos);
        ClientUDP client2(serverInfos);
        ClientUDP client3(serverInfos);

        server.bind(clienInfos);

        client0.launch();
        // Client 0

        while (server.getConnections().size() == 0)
            server.update();

        std::string login = "";


        login = server.getMessage(server.getConnections().at(0));

        ASSERT_STREQ("login", login.c_str());

        std::string ok("OK");
        ok += CR;
        ok += LF;

        server.addMessage(server.getConnections().at(0), ok);
        server.update();
        client0.join();

        //Client 1

        client1.launch();

        while (server.getConnections().size() == 1)
            server.update();

        login = "";
        login = server.getMessage(server.getConnections().at(1));

        ASSERT_STREQ("login", login.c_str());

        ok = "OK";
        ok += CR;
        ok += LF;

        server.addMessage(server.getConnections().at(1), ok);
        server.update();
        client1.join();

        //Client 2

        client2.launch();

        while (server.getConnections().size() == 2)
            server.update();

        login = "";
        login = server.getMessage(server.getConnections().at(2));

        ASSERT_STREQ("login", login.c_str());

        ok = "OK";
        ok += CR;
        ok += LF;

        server.addMessage(server.getConnections().at(2), ok);
        server.update();
        client2.join();

        //Client 3

        client3.launch();

        while (server.getConnections().size() == 3)
            server.update();

        login = "";
        login = server.getMessage(server.getConnections().at(3));

        ASSERT_STREQ("login", login.c_str());

        ok = "OK";
        ok += CR;
        ok += LF;

        server.addMessage(server.getConnections().at(3), ok);
        server.update();
        client3.join();
    }
    catch (network::SocketException &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

TEST(Network, SingleClientTcp)
{

    try
    {
        std::srand(std::time(0)); // use current time as seed for random generator
        unsigned short random_variable = std::rand() % 65000 + 2500;
        network::SockAddr clienInfos(random_variable);
        network::SockAddr serverInfos(random_variable, "127.0.0.1");

        network::ServerTCP server;
        ClientTCP client(serverInfos);

        server.bind(clienInfos);

        server.listen();

        client.launch();

        while (server.getConnections().size() == 0)
            server.update();

        std::string login = "";

        while ((login = server.getMessage(server.getConnections().at(0))) == "")
            server.update();

        ASSERT_STREQ("login", login.c_str());

        std::string ok("OK");
        ok += CR;
        ok += LF;

        server.addMessage(server.getConnections().at(0), ok);
        server.update();

        client.join();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

TEST(Network, TwoClientTcp)
{
    try
    {
        std::srand(std::time(0)); // use current time as seed for random generator
        unsigned short random_variable = std::rand() % 65000 + 2500;

        network::SockAddr clienInfos(random_variable);
        network::SockAddr serverInfos(random_variable, "127.0.0.1");

        network::ServerTCP server;

        ClientTCP client0(serverInfos);
        ClientTCP client1(serverInfos);

        server.bind(clienInfos);

        server.listen();

        client0.launch();

        while (server.getConnections().size() == 0)
            server.update();

        std::string login = "";

        // Client 0

        while ((login = server.getMessage(server.getConnections().at(0))) == "")
            server.update();

        ASSERT_STREQ("login", login.c_str());

        std::string ok("OK");
        ok += CR;
        ok += LF;

        server.addMessage(server.getConnections().at(0), ok);
        server.update();
        client0.join();

        client1.launch();

        while (server.getConnections().size() == 1)
            server.update();

        //Client 1
        login = "";
        while ((login = server.getMessage(server.getConnections().at(1))) == "") {
            server.update();
        }

        ASSERT_STREQ("login", login.c_str());

        ok = "OK";
        ok += CR;
        ok += LF;

        server.addMessage(server.getConnections().at(1), ok);
        server.update();
        client1.join();
    }
    catch (network::SocketException &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

TEST(Network, FourClientTcp)
{
    try
    {
        std::srand(std::time(0)); // use current time as seed for random generator
        unsigned short random_variable = std::rand() % 65000 + 2500;

        network::SockAddr clienInfos(random_variable);
        network::SockAddr serverInfos(random_variable, "127.0.0.1");

        network::ServerTCP server;

        ClientTCP client0(serverInfos);
        ClientTCP client1(serverInfos);
        ClientTCP client2(serverInfos);
        ClientTCP client3(serverInfos);

        server.bind(clienInfos);

        server.listen();

        client0.launch();
        // Client 0

        while (server.getConnections().size() == 0)
            server.update();

        std::string login = "";


        while ((login = server.getMessage(server.getConnections().at(0))) == "")
            server.update();

        ASSERT_STREQ("login", login.c_str());

        std::string ok("OK");
        ok += CR;
        ok += LF;

        server.addMessage(server.getConnections().at(0), ok);
        server.update();
        client0.join();

        //Client 1

        client1.launch();

        while (server.getConnections().size() == 1)
            server.update();

        login = "";
        while ((login = server.getMessage(server.getConnections().at(1))) == "") {
            server.update();
        }

        ASSERT_STREQ("login", login.c_str());

        ok = "OK";
        ok += CR;
        ok += LF;

        server.addMessage(server.getConnections().at(1), ok);
        server.update();
        client1.join();

        //Client 2

        client2.launch();

        while (server.getConnections().size() == 2)
            server.update();

        login = "";
        while ((login = server.getMessage(server.getConnections().at(2))) == "") {
            server.update();
        }

        ASSERT_STREQ("login", login.c_str());

        ok = "OK";
        ok += CR;
        ok += LF;

        server.addMessage(server.getConnections().at(2), ok);
        server.update();
        client2.join();

        //Client 3

        client3.launch();

        while (server.getConnections().size() == 3)
            server.update();

        login = "";
        while ((login = server.getMessage(server.getConnections().at(3))) == "") {
            server.update();
        }

        ASSERT_STREQ("login", login.c_str());

        ok = "OK";
        ok += CR;
        ok += LF;

        server.addMessage(server.getConnections().at(3), ok);
        server.update();
        client3.join();
    }
    catch (network::SocketException &e)
    {
        std::cerr << e.what() << std::endl;
    }
}


int main(int ac, char **av)
{
    ::testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
}