/**
 * @file Player.hpp
 * @author Benoit de Chezelles
 * @brief Class for a Player
 */

#ifndef PLAYER_HPP_
# define PLAYER_HPP_

# include <memory>
# include "Account.hpp"
# include "Network/ClientTCP.hh"

/**
 * Represent a Player
 */
class Player
{
public:
  /**
   * Construct a player
   */
  Player(Account const & account, std::shared_ptr<network::ClientTCP> const & sock);

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
  Account & getAccount();

protected:
  /**
   * Store the player's account
   */
  Account _account;
  std::shared_ptr<network::ClientTCP> _sock;
};

#endif /* !PLAYER_HPP_ */
