/**
 * @file main.cpp
 * @author Benoit de Chezelles
 * @brief Main server
 */

#include <iostream>
#include "Logs/Logger.hh"
#include "Logs/ErrorLogLevel.hh"
#include "Logs/InfoLogLevel.hh"
#include "ServerLogLevel.hh"
#include "Server.hpp"

int main()
{
  logs::getLogger().registerBasicsLogLevel();
  logs::getLogger().registerLogLevel(new logs::ServerLogLevel());

  Server server("my_little_server");

  unsigned short port = server.initNetwork(42403);
  if (port == 0)
    {
      logs::getLogger()[logs::ERRORS] << "There was an error while initializing server network" << std::endl;
      return EXIT_FAILURE;
    }
  logs::getLogger()[logs::INFO] << "The server is running on port " << port << "." << std::endl;

  server.run();
  return (0);
}
