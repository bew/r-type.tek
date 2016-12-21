/**
 * @file Player.cpp
 * @author Benoit de Chezelles
 * @brief Implementation for a Player
 */

#include "Player.hpp"

Player::Player(Account const & account, std::shared_ptr<network::ClientTCP> const & sock) :
  _account(account),
  _sock(sock)
{}

Account & Player::getAccount()
{
  return _account;
}
