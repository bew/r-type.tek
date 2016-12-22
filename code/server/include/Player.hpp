/**
 * @file Player.hpp
 * @author Benoit de Chezelles
 * @brief Class for a Player
 */

#ifndef PLAYER_HPP_
# define PLAYER_HPP_

# include <memory>
# include "Network/ClientTCP.hh"
# include "Account.hpp"
# include "ClientCommandsState.hpp"

/**
 * Represent a Player
 */
class Player
{
public:
  /**
   * Construct a player
   *
   * @param sock The client's control socket
   */
  Player(std::shared_ptr<network::ClientTCP> const & sock);

  /**
   * Destructor for a player
   */
  ~Player();

  Player(Player const & other) = delete;
  Player & operator=(Player const & other) = delete;

public:
  /**
   * Get the account associated with a player
   *
   * @return a reference on the account for this player
   */
  Account const & getAccount() const;

  /**
   * Get the account associated with a player
   *
   * @return a reference on the account for this player
   */
  Account & getAccount();

  /**
   * Get the control state of the player
   * It's usually used to change the player state.
   */
  ClientCommandsState & getControlState();

protected:
  /**
   * Store the player's account
   */
  Account _account;

  /**
   * Store the player's control socket
   */
  std::shared_ptr<network::ClientTCP> _sock;

  /**
   * Store the current player state
   */
  ClientCommandsState _controlState;
};

#endif /* !PLAYER_HPP_ */
