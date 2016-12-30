/**
 * @file ClientRouter.cpp
 * @author Benoit de Chezelles
 * @brief Implementation for the ClientRouter
 */

#include "Logs/Logger.hh"
#include "Protocol/Server.hh"

#include "ClientRouter.hpp"
#include "ServerLogLevel.hh"
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
  this->addRoute("GetAvailableRooms", BIND_THIS_P1(&ClientRouter::GetAvailableRoomsHandler));
}

bool ClientRouter::SignUpHandler(Request & req)
{
  if (!protocol::client::checkSignUp(req.getPacket()))
    return reply_bad_req(req, "The packet for the action 'SignUp' is not correct.");

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
  if (!protocol::client::checkLogin(req.getPacket()))
    return reply_bad_req(req, "The packet for the action 'Login' is not correct.");

  bson::Document const & rdata = req.getData();
  std::string username, password;

  rdata["username"] >> username;
  rdata["password"] >> password;

  if (!_server->_accounts.count(username))
    return reply_fail(req, pa::unauthorized(getTimestamp(req), "Unknown username/password"));

  Account const & account = _server->_accounts.at(username);
  if (! (account.password == password))
    return reply_fail(req, pa::unauthorized(getTimestamp(req), "Unknown username/password"));

  return reply_ok(req);
}

bool ClientRouter::LogoutHandler(Request & req)
{
  if (!protocol::client::checkLogout(req.getPacket()))
    return reply_bad_req(req, "The packet for the action 'Logout' is not correct.");

  bson::Document const & rdata = req.getData();

  // send to other players : (cumulative message ?)
  // if client was in game => send game leave
  // if client was in room => send room leave

  return reply_ok(req);
}

bool ClientRouter::RoomJoinHandler(Request & req)
{
  if (!protocol::client::checkRoomJoin(req.getPacket()))
    return reply_bad_req(req, "The packet for the action 'RoomJoin' is not correct.");

  bson::Document const & rdata = req.getData();
  std::string roomName;

  rdata["name"] >> roomName;

  std::shared_ptr<Player> player = _server->_players[req.getClient()];

  Room * room_ptr = nullptr;

  // room exists ?
  if (_server->_rooms.count(roomName))
    {
      Room & room = _server->_rooms.at(roomName);
      if (room.players.size() >= room.maximumSlots)
	return reply_fail(req, pa::tooManyRequests(getTimestamp(req), "The room '" + roomName + "' is full"));

      room.players[player->name] = player;
      player->currentRoom = roomName;
      room_ptr = &room;
    }
  else
    {
      // room name is valid ?
      if (!validInput(roomName))
	return reply_fail(req, pa::forbidden(getTimestamp(req), "Room name is not valid"));

      // create room(name, 4)
      _server->_rooms.emplace(roomName, Room(roomName, 4));
      Room & room = _server->_rooms.at(roomName);

      room.players[player->name] = player;
      room.master = player->name;
      player->currentRoom = roomName;
      room_ptr = &room;
    }

  Room & room = *room_ptr;

  bson::Document room_infos;
  bson::Document room_players;
  bson::Document room_generators;

  // gather room players list
  room_players << bson::Document::ARRAY_ENABLED;
  for (auto & kv : room.players)
    {
      std::shared_ptr<Player> & player = kv.second;
      room_players << player->name;
    }
  room_players << bson::Document::ARRAY_DISABLED;

  // TODO: gather room generators list
  room_generators << bson::Document::ARRAY_ENABLED;
  //for (auto & kv : room.generators)
  //  {
  //    std::shared_ptr<Generator> & generator = kv.second;
  //    room_generators << generator->name;
  //  }
  room_generators << bson::Document::ARRAY_DISABLED;

  room_infos << u8"players" << room_players;
  room_infos << u8"data" << room_generators;

  return reply_ok(req, room_infos);
}

bool ClientRouter::RoomLeaveHandler(Request & req)
{
  if (!protocol::client::checkRoomLeave(req.getPacket()))
    return reply_bad_req(req, "The packet for the action 'RoomLeave' is not correct.");

  std::shared_ptr<Player> player = _server->_players[req.getClient()];
  Room & room = _server->_rooms.at(player->currentRoom);

  send_to_room_players(req, room, protocol::server::roomLeave(player->name));

  return reply_ok(req);
}

bool ClientRouter::RoomKickHandler(Request & req)
{
  if (!protocol::client::checkRoomKick(req.getPacket()))
    return reply_bad_req(req, "The packet for the action 'RoomKick' is not correct.");

  bson::Document const & rdata = req.getData();
  std::string targetName;

  rdata["username"] >> targetName;

  std::shared_ptr<Player> player = _server->_players[req.getClient()];
  Room & room = _server->_rooms.at(player->currentRoom);

  if (room.master != player->name)
    return reply_fail(req, pa::forbidden(getTimestamp(req), "You are not the master of your room"));

  if (!_server->_players_by_name.count(targetName) || !room.players.count(targetName))
    return reply_fail(req, pa::notFound(getTimestamp(req), "No player named " + targetName));

  // remove player from room
  room.players.erase(targetName);

  // send ok to master
  reply_ok(req);

  // send notif to all players
  send_to_room_players(req, room, protocol::server::roomKick(targetName));

  return true;
}

bool ClientRouter::GameStartHandler(Request & req)
{
  if (!protocol::client::checkGameStart(req.getPacket()))
    return reply_bad_req(req, "The packet for the action 'GameStart' is not correct.");

  bson::Document const & rdata = req.getData();

  // prepare thread
  // prepare ECS ...

  // open UDP data socket

  // choose network auth-token for players
  // send to other players + auth token
  // FIXME: more ?

  return true;
}

bool ClientRouter::GameLeaveHandler(Request &req)
{
  if (!protocol::client::checkGameLeave(req.getPacket()))
    return reply_bad_req(req, "The packet for the action 'GameLeave' is not correct.");

  bson::Document const & rdata = req.getData();

  // send to other players

  return true;
}

bool ClientRouter::GetAvailableRoomsHandler(Request & req)
{
  if (!protocol::client::checkGetAvailableRooms(req.getPacket()))
    return reply_bad_req(req, "The packet for the action 'GetAvailableRooms' is not correct.");

  bson::Document rooms_data;
  rooms_data << bson::Document::ARRAY_ENABLED;
  for (auto & kv : _server->_rooms)
    {
      Room & room = kv.second;
      bson::Document room_data;

      room_data << u8"name" << room.name;
      room_data << u8"master" << room.master;
      room_data << u8"totalSlots" << room.maximumSlots;
      room_data << u8"availableSlots" << static_cast<int>(room.maximumSlots - room.players.size());

      rooms_data << room_data;
    }
  rooms_data << bson::Document::ARRAY_DISABLED;

  return reply_ok(req, rooms_data);
}

int64_t ClientRouter::getTimestamp(Request & req) const
{
  return req.getHeader()["timestamp"].getValueInt64();
}

bool ClientRouter::reply_bad_req(Request & req, std::string const & message) const
{
  logs::logger[logs::SERVER] << message << std::endl;
  return reply_fail(req, protocol::answers::badRequest(getTimestamp(req), message));
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
  if (input.empty())
    return false;
  return input.find(network::magic) == std::string::npos;
}

void ClientRouter::send_to_other_players(Request & req, bson::Document const & broadcast_msg) const
{
  for (auto & kv : _server->_players)
    {
      std::shared_ptr<Player> & player = kv.second;

      if (player->sock != req.getClient())
	player->sock->addMessage(broadcast_msg.getBufferString() + network::magic);
    }
}

void ClientRouter::send_to_room_players(Request & req, Room & room, bson::Document const & broadcast_msg) const
{
  for (auto & kv : room.players)
    {
      std::shared_ptr<Player> & player = kv.second;

      player->sock->addMessage(broadcast_msg.getBufferString() + network::magic);
    }
}

