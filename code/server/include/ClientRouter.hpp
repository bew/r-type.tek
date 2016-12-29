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

  int64_t getTimestamp(Request & req) const;

protected:
  Server * _server;
};
