/**
 * @file Server.cpp
 * @author Benoit de Chezelles
 * @brief Implementation for the server
 */

#include "Server.hpp"

Server::Server(std::string const & name) :
  _serverName(name)
{}

Server::~Server()
{}

void Server::run(unsigned int port)
{
  (void)port;
  // create server socket
}
