/**
 * @file Player.cpp
 * @author Benoit de Chezelles
 * @brief Implementation for a Player
 */

#include "Player.hpp"

Player::Player(std::shared_ptr<network::ClientTCP> const & sock) :
  _sock(sock),
  _account()
{}

Player::~Player()
{}

Account const & Player::getAccount() const
{
  return _account;
}

ClientCommandsState & Player::getControlState()
{
  return _controlState;
}
