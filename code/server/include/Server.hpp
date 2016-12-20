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
   * Construct a server instance, with a name on a specified port
   *
   * @param name The name of the server used for server identification on the network
   * @param port The port on which to start the server
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
   * @param nb_client_max The maximum number of client to handle.
   * @return The used port, 0 if there where an error.
   */
  unsigned initNetwork(unsigned port = 0);

  /**
   * Run the main server logic
   */
  void run();

protected:


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

  std::string _serverName;

  network::ServerTCP _serverSock;
};

#endif /* !SERVER_HPP_ */
