/**
 * @file ClientRouter.cpp
 * @author Benoit de Chezelles
 * @brief Implementation for the ClientRouter
 */

#include "ClientRouter.hpp"

#include "Server.hpp"

#define BIND_THIS_P1(HANDLER) std::bind(HANDLER, this, std::placeholders::_1)

ClientRouter::ClientRouter(Server & server) :
  _server(&server)
{
  this->addRoute("SignUp",    BIND_THIS_P1(&ClientRouter::SignUpHandler));
  this->addRoute("Login",     BIND_THIS_P1(&ClientRouter::LoginHandler));
  this->addRoute("Logout",    BIND_THIS_P1(&ClientRouter::LogoutHandler));
  this->addRoute("RoomLeave", BIND_THIS_P1(&ClientRouter::RoomLeaveHandler));
  this->addRoute("RoomKick",  BIND_THIS_P1(&ClientRouter::RoomKickHandler));
  this->addRoute("GameStart", BIND_THIS_P1(&ClientRouter::GameStartHandler));
  this->addRoute("GameLeave", BIND_THIS_P1(&ClientRouter::GameLeaveHandler));
}

bool ClientRouter::SignUpHandler(Request & req)
{
  bson::Document const & rdata = req.getData();
  std::string username, password;

  rdata["username"] >> username;
  rdata["password"] >> password;

  if (_server->_accounts.count(username))
    return reply_fail<protocol::answers::badRequest>(req, "Username " + username + " already taken.");

  _server->_accounts[username] = std::make_shared<Account>(username, password);

  return reply_ok(req);
}

bool ClientRouter::LoginHandler(Request & req)
{
  bson::Document const & rdata = req.getData();
  std::string username, password;

  rdata["username"] >> username;
  rdata["password"] >> password;

  if (!_server->_accounts.count(username))
    return reply_fail<protocol::answers::unauthorized>(req, "Unknown username/password");

  std::shared_ptr<Account> const account = _server->_accounts.at(username);
  if (! (account->getPassword() == password))
    return reply_fail<protocol::answers::unauthorized>(req, "Unknown username/password");

  return reply_ok(req);
}

bool ClientRouter::LogoutHandler(Request &)
{
  // send to other players : (cumulative message ?)
  // if client was in game => send game leave
  // if client was in room => send room leave
}

bool ClientRouter::RoomLeaveHandler(Request &)
{
  // send to other players
}

bool ClientRouter::RoomKickHandler(Request &)
{
  // send to targeted player
  // remove player from room

  // send to other players
}

bool ClientRouter::GameStartHandler(Request &)
{
  // prepare thread
  // prepare ECS ...

  // open UDP data socket

  // choose network token for players
  // send to other players + auth token
  // FIXME: more ?
}

bool ClientRouter::GameLeaveHandler(Request &)
{
  // send to other players
}
