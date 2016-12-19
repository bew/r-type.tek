/**
 * @file Room.hpp
 * @author Benoit de Chezelles
 * @brief Class for a Room
 */

#ifndef ROOM_HPP_
# define ROOM_HPP_

#include <vector>
#include <stdexcept>
#include <memory>
#include "Player.hpp"
//#include "Plugins.hpp"

class FullRoom : public std::runtime_error
{
public:
  FullRoom() :
    std::runtime_error("The room is full")
  {}
};

/**
 * Represent a Room where players can play
 *
 * The room hold a game, where a given number of players can play
 * together on one level, generated from the activated plugins
 */
class Room
{
public:
  /**
   * Construct an empty room With a given number of slots for players
   *
   * @param nbSlots The number of slots available
   */
  Room(unsigned int nbSlots);

  /**
   * Destructor for a room
   */
  ~Room();

private:
  Room(Room const & other);
  Room & operator=(Room const & other);

public:
  /**
   * Add a given player to the room
   *
   * @param player The player to add to the room
   * @return false if there is no more slot available
   */
  bool addPlayer(std::shared_ptr<Player> const & player);

protected:
  /**
   * Store the number of slot, representing the maximum number of player for this room
   */
  unsigned int _nbSlots;

  /**
   * Store the players ID currently in the room
   */
  std::vector<std::shared_ptr<Player>> _players;

  /**
   * Store the list of activated plugins for the level of this room
   *
   * TODO: see how to activate plugins for a given room ctor ? methods ?
   */
  //std::vector<std::shared_ptr<Plugin>> _activatedPlugins;
};

#endif /* !ROOM_HPP_ */
