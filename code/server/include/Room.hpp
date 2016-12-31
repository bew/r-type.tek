/**
 * @file Room.hpp
 * @author Benoit de Chezelles
 * @brief Class for a Room
 */

#ifndef ROOM_HPP_
# define ROOM_HPP_

#include <map>
#include <stdexcept>
#include <memory>
#include "Player.hpp"
#include "Game.hh"

/**
 * Represent a Room where players can play
 *
 * The room hold a game, where a given number of players can play
 */
struct Room
{
  /**
   * Construct an empty room with a maximum number of slots
   *
   * @param maximumSlots The number of slots available
   */
  Room(std::string const & name, int maximumSlots) :
    name(name),
    maximumSlots(maximumSlots),
    master("")
  {}

  /**
   * The room name
   */
  std::string name;

  /**
   * The master player name
   *
   * The master player is the admin of this room
   */
  std::string master;

  /**
   * The maximum number of slot for players
   */
  int maximumSlots;

  /**
   * The players currently in the room, by username
   */
  std::map<std::string, std::shared_ptr<Player>> players;

    /**
     * The Game of the room
     */
    Game *game;
};

#endif /* !ROOM_HPP_ */
