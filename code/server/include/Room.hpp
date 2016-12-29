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

/**
 * Represents a component flag exception, it's thrown when room error occured
 */
using RoomException = std::runtime_error;

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

  Room(Room const & other) = delete;
  Room & operator=(Room const & other) = delete;

public:
  /**
   * Add a given player to the room
   *
   * @param player The player to add to the room
   */
  void addPlayer(std::shared_ptr<Player> const & player);

  /**
   * Check if the Room is full
   *
   * @return true if the room is full, else false
   */
  bool isFull() const;

protected:
  /**
   * Store the number of slot, representing the maximum number of player for this room
   */
  unsigned int _nbSlots;

  /**
   * Store the players currently in the room
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
