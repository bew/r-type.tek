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

                if (isNewClient(from))
                    _clients.push_back(std::shared_ptr<ClientUDP>(new ClientUDP(from)));

                getClient(from)->getReadBuffer().fill(msg);
            }
            for (auto &client: _clients)
            {
                if (_selector.isWritable(_socket.getSocket()))
                {
                    std::string msg;
                    if ((msg = client->getWriteBuffer().get()) != "")
                    {
                        msg += CR;
                        msg += LF;
                        int nbBytesSend = _socket.send(client->getAddr(), msg);
                        client->getWriteBuffer().updatePosition(static_cast<size_t>(nbBytesSend ));

                        if (client->getMessage() == "")
                            _selector.unmonitor(_socket.getSocket(), NetworkSelect::WRITE);
                    }
                }
            }
        }
        catch (SocketException &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    void ServerUDP::add(const std::shared_ptr<ClientUDP> client, const std::string &msg)
    {
        client->addMessage(msg);
        if (*(--msg.end()) == CR || *(--msg.end()) == LF)
            _selector.monitor(_socket.getSocket(), NetworkSelect::WRITE);
    }

    std::string ServerUDP::get(const std::shared_ptr<ClientUDP> client)
    {
        return client->getMessage();
    }

    std::vector<std::shared_ptr<ClientUDP>> ServerUDP::getConnections() const
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
}