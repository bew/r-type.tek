/**
 * @file Server.cpp
 * @author Benoit de Chezelles
 * @brief Implementation for the server
 */

#include <iostream>
#include "BSON/Document.hh"
#include "Server.hpp"
#include "Network/SocketException.hh"

Server::Server(std::string const & name) :
  _serverName(name)
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
      return 0;
    }
  return addr.getPort();
}

void Server::run()
{
  while (true)
    {
      _serverSock.update();

      std::shared_ptr<network::ClientTCP> cl = _serverSock.getFirstClientWithMessage();
      while (cl)
	{
	  processMessage(cl);
	  cl = _serverSock.getFirstClientWithMessage();
	}
    }
}

void Server::processMessage(std::shared_ptr<network::ClientTCP> client)
{
  std::string const & raw_packet = client->getMessage();
  bson::Document packet(std::vector<unsigned char>(raw_packet.begin(), raw_packet.end()));

  // TODO: check packet header
  // TODO: based on the action, check the packet content

  std::string action;
  packet["action"] >> action;

  if (! _players.count(client)) // this is a new client
    _players[client] = std::make_shared<Player>(client);

  ClientCommandsState & state = _players.at(client)->getControlState();

  if (!state.gotoNextStateVia(action))
    ; // TODO: send error : request not allowed ?

  // process the request, execute the callback
  if (!callback())
  //   state.revertToPreviousState();
}
