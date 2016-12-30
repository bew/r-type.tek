/**
 * @file ClientRouter.cpp
 * @author Benoit de Chezelles
 * @brief Implementation for the ClientRouter
 */

#pragma once

class ClientRouter;

class Server;

#include "Protocol/Answers.hh"
#include "Router.hpp"

// TODO: doc
class ClientRouter : public Router
{
public:
  ClientRouter(Server & server);

  bool SignUpHandler(Request & req);
  bool LoginHandler(Request &);
  bool LogoutHandler(Request &);
  bool RoomLeaveHandler(Request &);
  bool RoomKickHandler(Request &);
  bool GameStartHandler(Request &);
  bool GameLeaveHandler(Request &);

protected:
  int64_t getTimestamp(Request & req) const;
  bool reply_fail(Request & req, bson::Document const & message) const;

  bool reply_ok(Request & req, std::string const & message = "") const;
  bool reply_ok(Request & req, bson::Document const & message) const;

  bool validInput(std::string const & input) const;

protected:
  Server * _server;
};
