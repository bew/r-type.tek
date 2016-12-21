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

  unsigned short port = server.initNetwork();
  if (port == 0)
    {
      std::cerr << "There was an error while initializing server network" << std::endl;
      return EXIT_FAILURE;
    }
  std::cout << "The server is running on port " << port << "." << std::endl;

  server.run();
  return (0);
}
