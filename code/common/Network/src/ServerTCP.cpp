/**
 * @file ServerTCP.cpp
 * @author Tookie
 * @brief representation of server tcp
 */

#include <iostream>
#include "ServerTCP.hh"
#include "SocketException.hh"
#include "Logs/Logger.hh"
#include "Logs/ErrorLogLevel.hh"

namespace network
{

    ServerTCP::ServerTCP() : _socketServer()
    {}

    ServerTCP::~ServerTCP()
    {
        close();
        for (auto &client: _clients)
            client->close();
    }

    std::shared_ptr<ClientTCP> ServerTCP::getFirstClientWithMessage() const
    {
        for (auto &client : _clients)
        {
            if (client->hasMessage())
                return client;
        }
        return nullptr;
    }

    void ServerTCP::update(unsigned long ms)
    {
        try
        {
            struct timeval timer;
            timer.tv_sec = ms / 1000;
            timer.tv_usec = (ms - (timer.tv_sec * 1000)) * 1000;
            _selector.select(&timer);
            if (_selector.isReadable(_socketServer.getSocket()))
                accept();
        }
        catch (SocketException &e)
        {
            deleteClosedConnections();
            if (logs::logger.isRegister(logs::ERRORS))
                logs::logger[logs::ERRORS] << e.what() << std::endl;
            else
                std::cerr << e.what() << std::endl;
        }
        for (auto client = _clients.begin(); client != _clients.end(); ++client)
        {
            try
            {
                (*client)->update(ms);
                if ((*client)->isClose())
                {
                    client = _clients.erase(client);
                    if (client == _clients.end())
                        break;
                }
            }
            catch (SocketException &e)
            {
                client = _clients.erase(client);
                if (client == _clients.end())
                    break;
                if (logs::logger.isRegister(logs::ERRORS))
                    logs::logger[logs::ERRORS] << e.what() << std::endl;
                else
                    std::cerr << e.what() << std::endl;
            }
        }
    }

    void ServerTCP::deleteClosedConnections()
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

    void ServerTCP::bind(SockAddr &hostInfos)
    {
        _socketServer.bind(hostInfos);
        _selector.monitor(_socketServer.getSocket(), NetworkSelect::READ);
    }

    void ServerTCP::listen()
    {
        _socketServer.listen();
    }

    void ServerTCP::accept()
    {
        Socket_t newConnection = _socketServer.accept();
        std::shared_ptr<ClientTCP> newClient = std::make_shared<ClientTCP>(newConnection);
        newClient->getSelector().monitor(newConnection, NetworkSelect::READ);
        _clients.push_back(newClient);
    }

    std::string ServerTCP::getMessage(const std::shared_ptr<ClientTCP> client)
    {
        return client->getMessage();
    }

    void ServerTCP::addMessage(const std::shared_ptr<ClientTCP> client, const std::string &message)
    {
        client->addMessage(message);
    }

    const std::vector<std::shared_ptr<ClientTCP>> &ServerTCP::getConnections() const
    {
        return _clients;
    }

    bool ServerTCP::isClose() const
    {
        return (_socketServer.getSocket() == -1);
    }

    void ServerTCP::close()
    {
        if (!isClose())
        {
            _selector.unmonitor(_socketServer.getSocket(), NetworkSelect::READ);
            _selector.unmonitor(_socketServer.getSocket(), NetworkSelect::WRITE);
            _socketServer.close();
        }
    }

    bool ServerTCP::hasMessage(std::shared_ptr<ClientTCP> client) const
    {
        return client->hasMessage();
    }

}
