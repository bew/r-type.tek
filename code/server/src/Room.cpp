/**
 * @file Room.cpp
 * @author Benoit de Chezelles
 * @brief Implementation of the Room
 */

#include "Room.hpp"

Room::Room(unsigned int nbSlots) :
  _nbSlots(nbSlots)
{}

bool Room::addPlayer(std::shared_ptr<Player> const & player)
{
  if (_players.size() >= _nbSlots)
    return false;

  _players.push_back(player);
  return true;
}

void Room::setActivatedPlugins(std::vector<std::string> const & plugins)
{
  _activatedPlugins = plugins;
}
