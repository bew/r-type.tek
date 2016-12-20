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

unsigned Server::initNetwork(unsigned port, unsigned nb_client_max)
{
  network::SockAddr addr(port);
  try
    {
      _serverSock.bind(addr);
      _serverSock.listen(nb_client_max);
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

}
