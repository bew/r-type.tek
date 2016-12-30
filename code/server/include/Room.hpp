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
  Room(std::string const & name, unsigned int maximumSlots) :
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
  unsigned int maximumSlots;

  /**
   * The players currently in the room
   */
  std::vector<std::shared_ptr<Player>> players;

  // ECS ?
  // UDP data socket ? (should be in ECS world)

  /**
   * Store the list of activated plugins for the level of this room
   *
   * TODO: see how to activate plugins for a given room ctor ? methods ?
   */
  //std::vector<std::shared_ptr<Plugin>> _activatedPlugins;
};

#endif /* !ROOM_HPP_ */
