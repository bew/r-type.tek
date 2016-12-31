/**
 * @file ServerRouter.cpp
 * @author Benoit de Chezelles
 * @brief Implementation for the ServerRouter
 */

#pragma once

class ServerRouter;

class Server;

#include "Protocol/Answers.hh"
#include "Router.hpp"
#include "Room.hpp"

/**
 * Represent the Server command router and handler
 */
class ServerRouter : public Router
{
private:
  typedef bool (handler_t)(Request &);

  handler_t SignUpHandler, LoginHandler, LogoutHandler;
  handler_t RoomJoinHandler, RoomLeaveHandler, RoomKickHandler;
  handler_t GameStartHandler, GameLeaveHandler;
  handler_t GetAvailableRoomsHandler;

public:
  /**
   * Construct a ServerRouter, which has full access to the given server
   *
   * @param server The associated server
   */
  ServerRouter(Server & server);

protected:
  /**
   * Extract the timestamp from a Request
   *
   * @param req The request to extract from
   * @return The timestamp
   */
  int64_t getTimestamp(Request & req) const;

  /**
   * Reply badRequest to the request sender with given message
   *
   * @param req The request to respond to
   * @param message The explain message of the badRequest
   * @return false
   */
  bool reply_bad_req(Request & req, std::string const & message) const;

  /**
   * Reply the given document to the request sender
   *
   * @param req The request to respond to
   * @param message The Document full of error explaination
   * @return false
   */
  bool reply_fail(Request & req, bson::Document const & message) const;

  /**
   * Reply a successfull answer to the request sender, with
   * additional data if needed
   *
   * @param req The request to respond to
   * @param ok_data Additional data for the response
   * @return true
   */
  bool reply_ok(Request & req, bson::Document const & ok_data = bson::Document()) const;

  /**
   * Check the validity of input (not empty, and not invalid)
   *
   * @param input The input to check
   * @return true if valid, else false
   */
  bool validInput(std::string const & input) const;

  /**
   * Send a command to all players of a Room except the sender
   *
   * @param req The request, used to get the sender
   * @param room The room
   * @param broadcast_msg The command to send
   */
  void send_to_room_other_players(Request & req, Room & room, bson::Document const & broadcast_msg) const;

  /**
   * Send a command to all players of a Room
   *
   * @param room The room
   * @param broadcast_msg The command to send
   */
  void send_to_room_players(Room & room, bson::Document const & broadcast_msg) const;

    void sendMessageToRequester(const Request& request, const bson::Document& document) const;

protected:
  Server * _server;
};
