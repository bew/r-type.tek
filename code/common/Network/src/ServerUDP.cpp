/**
 * @file ServerUDP.cpp
 * @author Tookie
 * @brief implementation of server udp
 */

#include <iostream>
#include <SocketException.hh>
#include "ServerUDP.hh"
#include "Logs/Logger.hh"
#include "Logs/ErrorLogLevel.hh"
namespace network
{
    ServerUDP::ServerUDP() : _socket()
    {
    }

    ServerUDP::~ServerUDP()
    {
        close();
        for (auto &client : _clients)
            client->close();
    }

    void ServerUDP::bind(SockAddr &hostInfos)
    {
        _socket.bind(hostInfos);
        _selector.monitor(_socket.getSocket(), NetworkSelect::READ);
    }

    void ServerUDP::update(unsigned long ms)
    {
        try
        {
            struct timeval timer;
            timer.tv_sec = ms / 1000;
            timer.tv_usec = (ms - (timer.tv_sec * 1000)) * 1000;
            _selector.select(&timer);
            if (_selector.isReadable(_socket.getSocket()))
            {
                SockAddr from(0, "");
                std::string msg = _socket.recv(from);

                if (this->isNewClient(from))
                    _clients.push_back(std::shared_ptr<ClientUDP>(new ClientUDP(from)));

                this->getClient(from)->getReadBuffer().fill(msg);
            }
        }
        catch (SocketException &e)
        {
            deleteClosedConnections();
            if (logs::getLogger().isRegister(logs::ERRORS))
                logs::getLogger()[logs::ERRORS] << e.what() << std::endl;
            else
                std::cerr << e.what() << std::endl;
        }
        for (auto client = _clients.begin(); client != _clients.end(); ++client)
        {
            try
            {
                if (_selector.isWritable(_socket.getSocket()))
                {
                    std::string msg;
                    if (!(msg = (*client)->getWriteBuffer().get()).empty())
                    {
                        msg += network::magic;
                        size_t nbBytesSend = _socket.send((*client)->getAddr(), msg);
                        (*client)->getWriteBuffer().updatePosition(nbBytesSend);

                        if ((*client)->getMessage().empty())
                            _selector.unmonitor(_socket.getSocket(), NetworkSelect::WRITE);
                    }
                }
            }
            catch (SocketException &e)
            {
                if ((*client)->isClose())
                {
                    client = _clients.erase(client);
                    if (client == _clients.end())
                        break;
                }
                if (logs::getLogger().isRegister(logs::ERRORS))
                    logs::getLogger()[logs::ERRORS] << e.what() << std::endl;
                else
                    std::cerr << e.what() << std::endl;
            }
        }

    }

    void ServerUDP::addMessage(const std::shared_ptr<ClientUDP> client, const std::string &msg)
    {
        client->addMessage(msg);
        if (msg.size() >= 8 && msg.substr(msg.length() - 8) == network::magic)
            _selector.monitor(_socket.getSocket(), NetworkSelect::WRITE);
    }

    std::string ServerUDP::getMessage(const std::shared_ptr<ClientUDP> client)
    {
        return client->getMessage();
    }

    const std::vector<std::shared_ptr<ClientUDP>> &ServerUDP::getConnections() const
    {
        return _clients;
    }

    bool ServerUDP::isNewClient(const SockAddr &addr)
    {
        for (auto &client : _clients)
        {
            if (addr == client->getAddr())
                return false;
        }
        return true;
    }

    std::shared_ptr<ClientUDP> ServerUDP::getClient(const SockAddr &addr)
    {
        for (auto &client : _clients)
        {
            if (addr == client->getAddr())
                return client;
        }
        return nullptr;
    }

    bool ServerUDP::isClose() const
    {
        return (_socket.getSocket() == -1);
    }

    void ServerUDP::close()
    {
        if (!isClose())
        {
            _selector.unmonitor(_socket.getSocket(), NetworkSelect::READ);
            _selector.unmonitor(_socket.getSocket(), NetworkSelect::WRITE);
            _socket.close();
        }
    }

    std::shared_ptr<ClientUDP> ServerUDP::getFirstClientWithMessage() const
    {
        for (auto &client : _clients)
        {
            if (client->hasMessage())
                return client;
        }
        return nullptr;
    }

    bool ServerUDP::hasMessage(std::shared_ptr<ClientUDP> client) const
    {
        return client->hasMessage();
    }

    void ServerUDP::deleteClosedConnections()
    {
        for (auto client = _clients.begin(); client != _clients.end(); ++client)
        {
            if ((*client)->isClose())
            {
                client = _clients.erase(client);
                if (client == _clients.end())
                    return;
            }
        }
    }
}