/**
 * @file main.cpp
 * @author Benoit de Chezelles
 * @brief Main server
 */

#include <iostream>
#include "Server.hpp"

int main()
{
  Server server("my_little_server");

  if (server.initNetwork(4242) == 0)
    {
      std::cerr << "There was an error while initializing server network" << std::endl;
      return EXIT_FAILURE;
    }

  server.run();
  return (0);
}
