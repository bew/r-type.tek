/**
 * @file Server.hpp
 * @author Benoit de Chezelles
 * @brief Class for the server
 */

#ifndef SERVER_HPP_
# define SERVER_HPP_

# include <string>
# include <vector>
# include <memory>
# include "Player.hpp"
# include "Room.hpp"
# include "Network/ServerTCP.hh"

/**
 * Represent the server
 */
class Server
{
public:
  /**
   * Construct a server instance, with a network name
   *
   * @param name The name of the server used for server identification on the network
   */
  Server(std::string const & name);

  /**
   * Destructor for the server
   */
  ~Server();

  Server(Server const & other) = delete;
  Server & operator=(Server const & other) = delete;

public:
  /**
   * Initialize the server's network
   *
   * @param port The port on which to bind the server. If not given, the first
   * available port will be taken.
   * @return The used port, 0 if there where an error.
   */
  unsigned initNetwork(unsigned short port = 0);

  /**
   * Run the main server logic
   */
  void run();

protected:
  /**
   * Store the players connected and authenticated to the server
   * They can be playing in a room or not.
   */
  std::vector<std::shared_ptr<Player>> _players;

  /**
   * Store the opened rooms
   */
  std::vector<Room> _rooms;

  /**
   * Store the server name for network identification
   */
  std::string _serverName;

  /**
   * Store the server socket
   */
  network::ServerTCP _serverSock;
};

#endif /* !SERVER_HPP_ */
