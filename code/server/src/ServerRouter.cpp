/**
 * @file ServerRouter.cpp
 * @author Benoit de Chezelles
 * @brief Implementation for the ServerRouter
 */

#include "Logs/Logger.hh"
#include "Protocol/Server.hh"
#include "FSWatcher/AFileSystemWatcher.hh"
#include "LibraryLoader/ALibraryLoader.hh"
#include "LibraryLoader/Dependent_ptr.hpp"

#include "ServerRouter.hpp"
#include "ServerLogLevel.hh"
#include "Server.hpp"

#define BIND_THIS_P1(HANDLER) std::bind(HANDLER, this, std::placeholders::_1)

namespace pa = protocol::answers;

ServerRouter::ServerRouter(Server & server) :
  _server(&server)
{
  this->addRoute("SignUp",    BIND_THIS_P1(&ServerRouter::SignUpHandler));
  this->addRoute("Login",     BIND_THIS_P1(&ServerRouter::LoginHandler));
  this->addRoute("Logout",    BIND_THIS_P1(&ServerRouter::LogoutHandler));
  this->addRoute("RoomJoin",  BIND_THIS_P1(&ServerRouter::RoomJoinHandler));
  this->addRoute("RoomLeave", BIND_THIS_P1(&ServerRouter::RoomLeaveHandler));
  this->addRoute("RoomKick",  BIND_THIS_P1(&ServerRouter::RoomKickHandler));
  this->addRoute("GameStart", BIND_THIS_P1(&ServerRouter::GameStartHandler));
  this->addRoute("GameLeave", BIND_THIS_P1(&ServerRouter::GameLeaveHandler));
  this->addRoute("GetAvailableRooms", BIND_THIS_P1(&ServerRouter::GetAvailableRoomsHandler));
}

bool ServerRouter::SignUpHandler(Request & req)
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

bool ServerRouter::LoginHandler(Request & req)
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

  std::shared_ptr<Player> player = _server->_players[req.getClient()];
  player->name = username;
  return reply_ok(req);
}

bool ServerRouter::LogoutHandler(Request & req)
{
  if (!protocol::client::checkLogout(req.getPacket()))
    return reply_bad_req(req, "The packet for the action 'Logout' is not correct.");

  std::shared_ptr<Player> player = _server->_players[req.getClient()];

  reply_ok(req);

  if (!player->currentRoom.empty() && _server->_rooms.count(player->currentRoom))
    {
      Room & room = _server->_rooms.at(player->currentRoom);
      if (room.players.count(player->name))
	{
	  // if client was in game => send game leave
	  if (player->isPlaying)
	    send_to_room_other_players(req, room, protocol::server::gameLeave(player->name));
	  player->isPlaying = false;
	}
      // if client was in room => send room leave
      send_to_room_other_players(req, room, protocol::server::roomLeave(player->name));

      room.players.erase(player->name);
      player->currentRoom.clear();
    }

  return true;
}

bool ServerRouter::RoomJoinHandler(Request & req)
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

    room_generators << bson::Document::ARRAY_ENABLED;
    std::string folder = "./generators/";
    FileSystemWatcher watcher(folder);
    for (const auto &i : watcher.processEvents()) {
        if (i.second == AFileSystemWatcher::Event::Add) {
            try {
                std::shared_ptr<LibraryLoader> module(new LibraryLoader(folder+i.first));
                Dependent_ptr<IGenerator, LibraryLoader> instance(module->newInstance(), module);
                room_generators << instance->getName();
            } catch (const LibraryLoaderException &e) {
                std::string errorMessage = std::string("Can't get the library name: ") + e.what();
                std::cerr << errorMessage << std::endl;
                logs::getLogger()[logs::SERVER] << errorMessage << std::endl;
            }
        }
    }
    room_generators << bson::Document::ARRAY_DISABLED;

  room_infos << u8"players" << room_players;
  room_infos << u8"generators" << room_generators;

  return reply_ok(req, room_infos);
}

bool ServerRouter::RoomLeaveHandler(Request & req)
{
  if (!protocol::client::checkRoomLeave(req.getPacket()))
    return reply_bad_req(req, "The packet for the action 'RoomLeave' is not correct.");

  std::shared_ptr<Player> player = _server->_players[req.getClient()];
  Room & room = _server->_rooms.at(player->currentRoom);

  reply_ok(req);
  send_to_room_players(room, protocol::server::roomLeave(player->name));

  room.players.erase(player->name);
  player->currentRoom.clear();

  return true;
}

bool ServerRouter::RoomKickHandler(Request & req)
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
  send_to_room_players(room, protocol::server::roomKick(targetName));

  return true;
}

bool ServerRouter::GameStartHandler(Request & req)
{
  // Check the request
  if (!protocol::client::checkGameStart(req.getPacket()))
    return reply_bad_req(req, "The packet for the action 'GameStart' is not correct.");

  int64_t timestamp = getTimestamp(req);

  std::shared_ptr<Player> player = _server->_players[req.getClient()];
  // Check if player is in the room
  if (_server->_rooms.count(player->currentRoom)) {
    this->sendMessageToRequester(req, pa::forbidden(timestamp, "Can't launch game, you are not in any room."));
    logs::getLogger()[logs::SERVER] << player->name << " try to launch a game but wasn't in a room" << std::endl;
    return false;
  }

  Room & room = _server->_rooms.at(player->currentRoom);
  // Check if player is the master
  if (room.master == player->name) {
    this->sendMessageToRequester(req, pa::forbidden(timestamp, "Can't launch game, you are not the room master."));
    logs::getLogger()[logs::SERVER] << player->name << " try to launch a game but wasn't the room master" << std::endl;
    return false;
  }

  // Check if the game is not already started or done
  if (room.game != nullptr) {
    if (!room.game->isDone()) {
      this->sendMessageToRequester(req, pa::forbidden(timestamp, "The game is already started."));
      logs::getLogger()[logs::SERVER] << player->name << " try to launch a game but it was already started" << std::endl;
      return false;
    }
      else {
      delete room.game;
    }
  }

  //  Check the generator name
  bson::Document const & rdata = req.getData();
  std::string generatorName = rdata["generator"].getValueString();
  std::vector<std::string> generators = this->getAvailableGenerators();
  if (std::find(generators.begin(), generators.end(), generatorName) == generators.end()) {
    this->sendMessageToRequester(req, pa::notFound(timestamp, "Unknow generator '" + generatorName + "'"));
    logs::getLogger()[logs::SERVER] << player->name << " try to launch a game with unknow generator '" << generatorName << "'" << std::endl;
    // TODO: Return the available generators with command
    return false;
  }

  // Get the clients tokens
  std::vector<std::string> clientsTokens;
  for (const auto& kv : room.players)
    clientsTokens.push_back(kv.second->token);


  // Launch the Game
  room.game = new Game(room, generatorName, _server->_serverToken, clientsTokens);
    try {
        room.game->initECS();
        room.game->launch();
    }
    catch (const std::exception &e) {
      delete room.game;
      std::string errorMessage = "Error while launching the game of the room with owner '" + room.master + "': " + e.what();
      std::cerr << errorMessage << std::endl;
      logs::getLogger()[logs::SERVER] << errorMessage << std::endl;

      this->sendMessageToRequester(req, pa::internalServerError(timestamp, "Can't launch the game.").getBufferString() + network::magic);
      return false;
    }
    // After this point, we assume that startup went well and the game is now started
    room.game->detach();

  // set players as playing
  for (auto & kv : room.players)
    kv.second->isPlaying = true;

  reply_ok(req);

  // send GameStart to all players
  for (const auto& kv : room.players)
    kv.second->sock->addMessage(protocol::server::gameStart(room.game->getServerUdpPort(),
                                                            kv.second->token,
                                                            _server->_serverToken).getBufferString() + network::magic);
}

bool ServerRouter::GameLeaveHandler(Request &req)
{
    if (!protocol::client::checkGameLeave(req.getPacket()))
        return reply_bad_req(req, "The packet for the action 'GameLeave' is not correct.");

    std::shared_ptr<Player> player = _server->_players[req.getClient()];
    Room & room = _server->_rooms.at(player->currentRoom);

    if (room.players.count(player->name))
    {
        if (player->isPlaying)
            send_to_room_other_players(req, room, protocol::server::gameLeave(player->name));
        player->isPlaying = false;
    }

    return true;
}

bool ServerRouter::GetAvailableRoomsHandler(Request & req)
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

int64_t ServerRouter::getTimestamp(Request & req) const
{
  return req.getHeader()["timestamp"].getValueInt64();
}

bool ServerRouter::reply_bad_req(Request & req, std::string const & message) const
{
  logs::getLogger()[logs::SERVER] << message << std::endl;
  return reply_fail(req, pa::badRequest(getTimestamp(req), message));
}

bool ServerRouter::reply_fail(Request & req, bson::Document const & message) const
{
  req.getClient()->addMessage(message.getBufferString() + network::magic);
  return false;
}

bool ServerRouter::reply_ok(Request & req, bson::Document const & ok_data) const
{
  req.getClient()->addMessage(pa::ok(getTimestamp(req), ok_data).getBufferString() + network::magic);
  return true;
}

bool ServerRouter::validInput(std::string const & input) const
{
  if (input.empty())
    return false;
  return input.find(network::magic) == std::string::npos;
}

void ServerRouter::send_to_room_other_players(Request & req, Room & room, bson::Document const & broadcast_msg) const
{
  for (auto & kv : room.players)
    {
      std::shared_ptr<Player> & player = kv.second;

      if (player->sock != req.getClient())
	player->sock->addMessage(broadcast_msg.getBufferString() + network::magic);
    }
}

void ServerRouter::send_to_room_players(Room & room, bson::Document const & broadcast_msg) const
{
  for (auto & kv : room.players)
    {
      std::shared_ptr<Player> & player = kv.second;

      player->sock->addMessage(broadcast_msg.getBufferString() + network::magic);
    }
}

void ServerRouter::sendMessageToRequester(const Request& request, const bson::Document &document) const {
  request.getClient()->addMessage(document.getBufferString() + network::magic);
}

std::vector<std::string> ServerRouter::getAvailableGenerators() const {
  std::vector<std::string> generators;
  std::string folder = "./generators/";
  FileSystemWatcher watcher(folder);

  for (const auto &i : watcher.processEvents()) {
    if (i.second == AFileSystemWatcher::Event::Add) {
      try {
        std::shared_ptr<LibraryLoader> module(new LibraryLoader(folder+i.first));
        Dependent_ptr<IGenerator, LibraryLoader> instance(module->newInstance(), module);
        generators.push_back(instance->getName());
      } catch (const LibraryLoaderException &e) {
        std::string errorMessage = std::string("Can't get the library name: ") + e.what();
        std::cerr << errorMessage << std::endl;
        logs::getLogger()[logs::SERVER] << errorMessage << std::endl;
      }
    }
  }

  return generators;
}
