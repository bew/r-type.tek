/**
 * @file Player.hpp
 * @author Benoit de Chezelles
 * @brief Class for a Player
 */

#ifndef PLAYER_HPP_
# define PLAYER_HPP_

# include <memory>
# include <sstream>
# include "Network/ClientTCP.hh"
# include "ClientCommandsState.hpp"

/**
 * Represent a Player
 */
struct Player
{
  /** Construct a player
   *
   * @param sock The client's control socket
   */
  Player(std::shared_ptr<network::ClientTCP> const & sock) :
    sock(sock),
    isPlaying(false),
    name("")
  {
      std::stringstream ss;
      ss << this;
      token = ss.str();
  };

  /**
   * The player's username
   */
  std::string name;

  /**
   * The player's current room name
   */
  std::string currentRoom;

  /**
   * The player is in a game, playing
   */
  bool isPlaying;

  /**
   * Store the player's control socket
   */
  std::shared_ptr<network::ClientTCP> sock;

  /**
   * The player control state machine
   */
  ClientCommandsState controlState;

    /**
     * The token to use for UDP requests
     */
    std::string token;
};

#endif /* !PLAYER_HPP_ */
