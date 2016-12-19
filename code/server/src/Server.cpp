/**
 * @file Server.cpp
 * @author Benoit de Chezelles
 * @brief Implementation for the server
 */

#include <iostream>
#include "Server.hpp"
#include "Network/SocketException.hh"

Server::Server(std::string const & name) :
  _serverName(name)
{}

Server::~Server()
{}

unsigned Server::initNetwork(unsigned port)
{
  _serverSock.close();

  network::SockAddr addr(port);
  try
    {
      _serverSock.bind(addr);
    }
  catch (network::SocketException const & e)
    {
      std::cerr << "server:init: " << e.what() << std::endl;
      return 0;
    }
  return port; // TODO: use addr.getPort() to resolve port when port == 0
}

void Server::run()
{

}
