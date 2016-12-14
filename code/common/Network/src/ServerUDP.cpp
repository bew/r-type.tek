/**
 * @file ServerUDP.cpp
 * @author Tookie
 * @brief implementation of server udp
 */

#include <iostream>
#include <SocketException.hh>
#include "ServerUDP.hpp"

namespace network
{
    ServerUDP::ServerUDP() : _socket()
    {
    }

    ServerUDP::~ServerUDP()
    {
        close();
        for (auto& client : _clients)
            client->close();
    }

    void ServerUDP::bind(const SockAddr &hostInfos)
    {
        _socket.bind(hostInfos);
        _selector.monitor(_socket.getSocket(), NetworkSelect::READ);
    }

    void ServerUDP::update()
    {
        try
        {
            struct timeval timer;
            timer.tv_sec = 1;
            timer.tv_usec = 0;
            _selector.select(&timer);
            if (_selector.isReadable(_socket.getSocket()))
            {
                SockAddr from(0, "");
                std::string msg = _socket.recv(from);

                if (this->isNewClient(from))
                    _clients.push_back(std::shared_ptr<ClientUDP>(new ClientUDP(from)));

                this->getClient(from)->getReadBuffer().fill(msg);
            }
            for (auto &client: _clients)
            {
                if (_selector.isWritable(_socket.getSocket()))
                {
                    std::string msg;
                    if (!(msg = client->getWriteBuffer().get()).empty())
                    {
                        msg += CR;
                        msg += LF;
                        size_t nbBytesSend = _socket.send(client->getAddr(), msg);
                        client->getWriteBuffer().updatePosition(nbBytesSend);

                        if (client->getMessage().empty())
                            _selector.unmonitor(_socket.getSocket(), NetworkSelect::WRITE);
                    }
                }
            }
        }
        catch (SocketException &e)
        {
            throw e;
        }
    }

    void ServerUDP::addMessage(const std::shared_ptr<ClientUDP> client, const std::string &msg)
    {
        client->addMessage(msg);
        if (*(--msg.end()) == CR || *(--msg.end()) == LF)
            _selector.monitor(_socket.getSocket(), NetworkSelect::WRITE);
    }

    std::string ServerUDP::getMessage(const std::shared_ptr<ClientUDP> client)
    {
        return client->getMessage();
    }

    const std::vector<std::shared_ptr<ClientUDP>>& ServerUDP::getConnections() const
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
}