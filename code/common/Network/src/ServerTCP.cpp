/**
 * @file ServerTCP.cpp
 * @author Tookie
 * @brief representation of server tcp
 */



#include <iostream>
#include "ServerTCP.hpp"
#include "SocketException.hh"

namespace network
{

    ServerTCP::ServerTCP() : _socketServer()
    {
    }

    ServerTCP::~ServerTCP()
    {
        _selector.unmonitor(_socketServer.getSocket(), NetworkSelect::READ);
        _socketServer.close();
        for (auto &client: _clients)
            _selector.unmonitor(client->getSocket().getSocket(), NetworkSelect::READ);
    }

    void ServerTCP::update()
    {
        try
        {
            struct timeval timer;
            timer.tv_sec = 1;
            timer.tv_usec = 0;
            _selector.select(&timer);
            if (_selector.isReadable(_socketServer.getSocket()))
                accept();

            for (auto client = _clients.begin(); client != _clients.end(); ++client)
            {
                if (_selector.isReadable((*client)->getSocket().getSocket()))
                {
                    std::string msg = (*client)->getSocket().recv();
                    (*client)->getReadBuffer().fill(msg);
                    if ((*client)->isClose())
                    {
                        client = _clients.erase(client);
                        if (client == _clients.end())
                            break;
                    }
                }
                if (_selector.isWritable((*client)->getSocket().getSocket()))
                {
                    std::string msg;
                    if ((msg = (*client)->getWriteBuffer().get()) != "")
                    {
                        msg += CR;
                        msg += LF;
                        int nbBytesSend = (*client)->getSocket().send(msg);
                        (*client)->getWriteBuffer().updatePosition(static_cast<size_t>(nbBytesSend ));

                        if ((*client)->getWriteBuffer().get() == "")
                            _selector.unmonitor((*client)->getSocket().getSocket(), NetworkSelect::WRITE);
                    }
                }
            }
        }
        catch (SocketException &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    void ServerTCP::bind(const SockAddr& hostInfos)
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
        _selector.monitor(newConnection, NetworkSelect::READ);
        _clients.push_back(std::shared_ptr<ClientTCP>(new ClientTCP(newConnection)));
    }

    std::string ServerTCP::getMessage(const std::shared_ptr<ClientTCP> client)
    {
        return client->getMessage();
    }

    void ServerTCP::add(const std::shared_ptr<ClientTCP> client, const std::string &message)
    {
        client->addMessage(message);
        if (*(--message.end()) == CR || *(--message.end()) == LF)
            _selector.monitor(client->getSocket().getSocket(), NetworkSelect::WRITE);
    }

    const std::vector<std::shared_ptr<ClientTCP>> &ServerTCP::getConnections() const
    {
        return _clients;
    }

}
