/**
 * @file Server.cpp
 * @author Benoit de Chezelles
 * @brief Implementation for the server
 */

#include <iostream>
#include "BSON/Document.hh"
#include "Protocol/Answers.hh"
#include "Network/SocketException.hh"
#include "Logs/Logger.hh"
#include "ServerLogLevel.hh"
#include "Server.hpp"

Server::Server(std::string const & name) :
  _serverName(name),
  _clientRouter(*this)
{}

Server::~Server()
{}

unsigned short Server::initNetwork(unsigned short port)
{
  network::SockAddr addr(port);
  try
    {
      _serverSock.bind(addr);
      _serverSock.listen();
    }
  catch (network::SocketException const & e)
    {
      std::cerr << "server:init: " << e.what() << std::endl;
      logs::logger[logs::SERVER] << "init network error: " << e.what() << std::endl;
      return 0;
    }
  return addr.getPort();
}

void Server::run() {
    while (true) {
        _serverSock.update();

        std::shared_ptr<network::ClientTCP> cl = _serverSock.getFirstClientWithMessage();
        while (cl) {
            processMessage(cl);
            cl = _serverSock.getFirstClientWithMessage();
        }
    }
}

void Server::processMessage(std::shared_ptr<network::ClientTCP> client)
{
  std::string const & raw_packet = client->getMessage();
    bson::Document packet;
    try {
        packet = bson::Document(raw_packet);
    }
    catch (const bson::BsonException &e) {
        client->addMessage(protocol::answers::badRequest(-1, "Can't deserialize packet").getBufferString() + network::magic);
        logs::logger[logs::SERVER] << "Received a packet but can't deserialize it. " << e.what() << std::endl;
        return;
    }

    if (!protocol::checkMessage(packet)) {
        client->addMessage(protocol::answers::badRequest(-1, "Wrong packet format").getBufferString() + network::magic);
        logs::logger[logs::SERVER] << "Received a packet but wrong format : " << packet.toJSON(2) << std::endl;
        return;
    }
    logs::logger[logs::SERVER] << "Received a valid packet :" << std::endl << packet.toJSON(2) << std::endl;

    int64_t timestamp;
    std::string action;

    bson::Document const & header = packet["header"].getValueDocument();
    header["timestamp"] >> timestamp;
    header["action"] >> action;

    if (! _players.count(client)) // this is a new client
    {
        _players[client] = std::make_shared<Player>(client);
        logs::logger[logs::SERVER] << "New client connected (at:" << client << ")" << std::endl;
    }

  ClientCommandsState & state = _players.at(client)->getControlState();

  logs::logger[logs::SERVER] << "Client " << client
                             << " try action '" << action
                             << "' current state is '" << state.getCurrentState()->getName() << "'" << std::endl;

  if (!state.gotoNextStateVia(action))
    {
      logs::logger[logs::SERVER] << "Unauthorized action '" << action << "'" << std::endl;
      client->addMessage(protocol::answers::unauthorized(timestamp).getBufferString() + network::magic);
      return;
    }

  if (! _clientRouter.routePacket(packet, client))
    {
      state.revertToPreviousState();
      return;
    }
  logs::logger[logs::SERVER] << "Client state is now '" << state.getCurrentState()->getName() << "'" << std::endl;
}
