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

private:
  Server(Server const & other);
  Server & operator=(Server const & other);

public:
  /**
   * Run the main server logic
   */
  void run(unsigned int port);

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

  // socket for server
};

#endif /* !SERVER_HPP_ */
