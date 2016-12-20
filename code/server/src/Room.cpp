/**
 * @file Room.cpp
 * @author Benoit de Chezelles
 * @brief Implementation of the Room
 */

#include "Room.hpp"

Room::Room(unsigned int nbSlots) :
  _nbSlots(nbSlots)
{}

Room::~Room()
{}

void Room::addPlayer(std::shared_ptr<Player> const & player)
{
  if (_players.size() >= _nbSlots)
    throw FullRoom();

  _players.push_back(player);
}
