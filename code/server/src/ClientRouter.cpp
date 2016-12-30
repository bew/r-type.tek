/**
 * @file ClientRouter.cpp
 * @author Benoit de Chezelles
 * @brief Implementation for the ClientRouter
 */

#include "ClientRouter.hpp"

#include "Protocol/Server.hh"
#include "Server.hpp"

#define BIND_THIS_P1(HANDLER) std::bind(HANDLER, this, std::placeholders::_1)

namespace pa = protocol::answers;

ClientRouter::ClientRouter(Server & server) :
  _server(&server)
{
  this->addRoute("SignUp",    BIND_THIS_P1(&ClientRouter::SignUpHandler));
  this->addRoute("Login",     BIND_THIS_P1(&ClientRouter::LoginHandler));
  this->addRoute("Logout",    BIND_THIS_P1(&ClientRouter::LogoutHandler));
  this->addRoute("RoomJoin",  BIND_THIS_P1(&ClientRouter::RoomJoinHandler));
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

  if (!validInput(username) || !validInput(password))
    return reply_fail(req, pa::badRequest(getTimestamp(req), "Username or password have invalid chars"));

  if (_server->_accounts.count(username))
    return reply_fail(req, pa::badRequest(getTimestamp(req), "Username " + username + " already taken."));

  _server->_accounts[username] = Account {username, password};

  return reply_ok(req);
}

bool ClientRouter::LoginHandler(Request & req)
{
  bson::Document const & rdata = req.getData();
  std::string username, password;

  rdata["username"] >> username;
  rdata["password"] >> password;

  if (!_server->_accounts.count(username))
    return reply_fail(req, pa::unauthorized(getTimestamp(req), "Unknown username/password"));

  Account const & account = _server->_accounts.at(username);
  if (! (account.password == password))
    return reply_fail(req, pa::unauthorized(getTimestamp(req), "Unknown username/password"));

  // TODO: create a player, store association username-player
  return reply_ok(req);
}

bool ClientRouter::LogoutHandler(Request & req)
{
  // send to other players : (cumulative message ?)
  // if client was in game => send game leave
  // if client was in room => send room leave

  return reply_ok(req);
}

bool ClientRouter::RoomJoinHandler(Request & req)
{
  bson::Document const & rdata = req.getData();
  std::string roomName;

  rdata["name"] >> roomName;

  std::shared_ptr<Player> player = _server->_players[req.getClient()];

  // room exists ?
  if (_server->_rooms.count(roomName))
    {
      Room & room = _server->_rooms.at(roomName);
      if (room.players.size() >= room.maximumSlots)
	return reply_fail(req, pa::tooManyRequests(getTimestamp(req), "The room '" + roomName + "' is full"));

      room.players.push_back(player);
      player->currentRoom = roomName;
      return reply_ok(req);
    }

  // room name is not valid ?
  if (!validInput(roomName))
    return reply_fail(req, pa::forbidden(getTimestamp(req), "Room name is not valid"));

  // create room(name, 4)
  _server->_rooms.emplace(roomName, Room(roomName, 4));
  Room & room = _server->_rooms.at(roomName);

  room.players.push_back(player);
  room.master = player->name;
  player->currentRoom = roomName;

  return reply_ok(req);
}

bool ClientRouter::RoomLeaveHandler(Request & req)
{
  bson::Document const & rdata = req.getData();
  std::string username;

  rdata["username"] >> username;

  auto const & broadcast_msg = protocol::server::roomLeave(username);
  for (auto & kv : _server->_players)
    {
      std::shared_ptr<Player> & player = kv.second;

      if (player->sock != req.getClient())
	player->sock->addMessage(broadcast_msg.getBufferString() + network::magic);
    }

  return reply_ok(req);
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

  // choose network auth-token for players
  // send to other players + auth token
  // FIXME: more ?
}

bool ClientRouter::GameLeaveHandler(Request &)
{
  // send to other players
}

int64_t ClientRouter::getTimestamp(Request & req) const
{
  return req.getHeader()["timestamp"].getValueInt64();
}

bool ClientRouter::reply_fail(Request & req, bson::Document const & message) const
{
  req.getClient()->addMessage(message.getBufferString() + network::magic);
  return false;
}

bool ClientRouter::reply_ok(Request & req, std::string const & message) const
{
  if (message.empty())
    return reply_ok(req, pa::ok(getTimestamp(req)));
  else
    return reply_ok(req, pa::ok(getTimestamp(req), message));
}

bool ClientRouter::reply_ok(Request & req, bson::Document const & message) const
{
  req.getClient()->addMessage(message.getBufferString() + network::magic);
  return true;
}

bool ClientRouter::validInput(std::string const & input) const
{
  return input.find(network::magic) == std::string::npos;
}
