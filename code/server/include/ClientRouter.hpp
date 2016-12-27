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
  template <typename AnswerType, typename... Args>
  bool reply(bool returnValue, Request & req, Args &&... args);

  template <typename AnswerType, typename... Args>
  bool reply_fail(Request & req, Args &&... args);

  template <typename... Args>
  bool reply_ok(Request & req, Args &&... args);

protected:
  Server * _server;
};


template <typename AnswerType, typename... Args>
bool ClientRouter::reply(bool returnValue, Request & req, Args &&... args)
{
  int64_t timestamp = req.getHeader()["timestamp"].getValueInt64();

  auto const & answer = AnswerType(timestamp, std::forward<Args>(args)...);
  req.getClient()->addMessage(answer);
  return returnValue;
}

template <typename AnswerType, typename... Args>
bool ClientRouter::reply_fail(Request & req, Args &&... args)
{
  return reply<AnswerType>(false, req, std::forward<Args>(args)...);
}

template <typename... Args>
bool ClientRouter::reply_ok(Request & req, Args &&... args)
{
  return reply<protocol::answers::ok>(true, req, std::forward<Args>(args)...);
}
