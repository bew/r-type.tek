/**
 * @file ServerRouter.cpp
 * @author Benoit de Chezelles
 * @brief Implementation for the ServerRouter
 */

#include "Logs/Logger.hh"
#include "Protocol/Server.hh"
#include "FSWatcher/AFileSystemWatcher.hh"

#include "ServerRouter.hpp"
#include "ServerLogLevel.hh"
#include "Server.hpp"

#define BIND_THIS_P1(HANDLER) std::bind(HANDLER, this, std::placeholders::_1)

namespace pa = protocol::answers;

ServerRouter::ServerRouter(Server & server) :
  _server(&server)
{
    this->addRoute("SignUp", BIND_THIS_P1(&ServerRouter::SignUpHandler));
    this->addRoute("Login", BIND_THIS_P1(&ServerRouter::LoginHandler));
    this->addRoute("Logout", BIND_THIS_P1(&ServerRouter::LogoutHandler));
    this->addRoute("RoomJoin", BIND_THIS_P1(&ServerRouter::RoomJoinHandler));
    this->addRoute("RoomLeave", BIND_THIS_P1(&ServerRouter::RoomLeaveHandler));
    this->addRoute("RoomKick", BIND_THIS_P1(&ServerRouter::RoomKickHandler));
    this->addRoute("GameStart", BIND_THIS_P1(&ServerRouter::GameStartHandler));
    this->addRoute("GameLeave", BIND_THIS_P1(&ServerRouter::GameLeaveHandler));
    this->addRoute("GetAvailableRooms", BIND_THIS_P1(&ServerRouter::GetAvailableRoomsHandler));
    this->addRoute("GetAvailableGenerators", BIND_THIS_P1(&ServerRouter::GetAvailableGenerators));
}

bool ServerRouter::SignUpHandler(Request & req)
{
    // Check the integrity of the packet for the following action
    if (!protocol::client::checkSignUp(req.getPacket())) {
        std::string errorMessage = "The packet for the action 'SignUp' is not correct.";
        logs::getLogger()[logs::SERVER] << errorMessage << _server->getClientInformation(req.getClient()) << std::endl;
        return replyFail(req, pa::badRequest(-1, errorMessage));
    }

    bson::Document const &rdata = req.getData();
    std::string username, password;
    int64_t timestamp = getTimestamp(req);

    rdata["username"] >> username;
    rdata["password"] >> password;

    // Check if account is available
    if (_server->_accounts.count(username)) {
        std::string errorMessage = "Username " + username + " already taken.";
        logs::getLogger()[logs::SERVER] << errorMessage << _server->getClientInformation(req.getClient()) << std::endl;
        return replyFail(req, pa::badRequest(timestamp, errorMessage));
    }

    _server->_accounts[username] = Account {username, password};

    logs::getLogger()[logs::SERVER] << "Has Signup." << _server->getClientInformation(req.getClient()) << std::endl;
    return replyOk(req);
}

bool ServerRouter::LoginHandler(Request & req)
{
    // Check the integrity of the packet for the following action
    if (!protocol::client::checkLogin(req.getPacket())) {
        std::string errorMessage = "The packet for the action 'Login' is not correct.";
        logs::getLogger()[logs::SERVER] << errorMessage << _server->getClientInformation(req.getClient()) << std::endl;
        return replyFail(req, pa::badRequest(-1, errorMessage));
    }

    bson::Document const &rdata = req.getData();
    std::string username, password;
    int64_t timestamp = getTimestamp(req);

    rdata["username"] >> username;
    rdata["password"] >> password;

    // Check if the username has an account
    if (!_server->_accounts.count(username)) {
        logs::getLogger()[logs::SERVER] << "The username '" << username << "' doesn't exist." << _server->getClientInformation(req.getClient()) << std::endl;
        return replyFail(req, pa::unauthorized(timestamp, "Invalid username/password"));
    }

    // Check if the password if correct for the retrieved account
    Account const &account = _server->_accounts.at(username);
    if (!(account.password == password)) {
        logs::getLogger()[logs::SERVER] << "The password for '" << username << "' is invalid." << _server->getClientInformation(req.getClient()) << std::endl;
        return replyFail(req, pa::unauthorized(getTimestamp(req), "Invalid username/password"));
    }

    std::shared_ptr<Player> player = _server->_players[req.getClient()];
    player->name = username;
    logs::getLogger()[logs::SERVER] << "Has Login." << _server->getClientInformation(req.getClient()) << std::endl;
    return replyOk(req);
}

bool ServerRouter::LogoutHandler(Request & req)
{
    // Check the integrity of the packet for the following action
    if (!protocol::client::checkLogout(req.getPacket())) {
        std::string errorMessage = "The packet for the action 'Logout' is not correct.";
        logs::getLogger()[logs::SERVER] << errorMessage << _server->getClientInformation(req.getClient()) << std::endl;
        return replyFail(req, pa::badRequest(-1, errorMessage));
    }

    // Check if player connected
    if (!this->isPlayerConnected(req))
        return false;

    std::shared_ptr<Player> player = _server->_players[req.getClient()];

    replyOk(req);

    _server->disconnectClient(req.getClient(), true);

    logs::getLogger()[logs::SERVER] << "Has Logout." << _server->getClientInformation(req.getClient()) << std::endl;
    return true;
}

bool ServerRouter::RoomJoinHandler(Request & req)
{
    // Check the integrity of the packet for the following action
    if (!protocol::client::checkRoomJoin(req.getPacket())) {
        std::string errorMessage = "The packet for the action 'RoomJoin' is not correct.";
        logs::getLogger()[logs::SERVER] << errorMessage << _server->getClientInformation(req.getClient()) << std::endl;
        return replyFail(req, pa::badRequest(-1, errorMessage));
    }

    // Check if player connected
    if (!this->isPlayerConnected(req))
        return false;
    std::shared_ptr<Player> player = _server->_players[req.getClient()];

    int64_t timestamp = getTimestamp(req);

    bson::Document const &rdata = req.getData();
    std::string roomName;
    rdata["name"] >> roomName;

    Room *roomPtr = nullptr;
    // room exists ?
    if (_server->_rooms.count(roomName)) {
        Room &room = _server->_rooms.at(roomName);

        // If room is full
        if (room.players.size() >= room.maximumSlots) {
            std::string errorMessage = "The room '" + roomName + "' is full";
            logs::getLogger()[logs::SERVER] << errorMessage << _server->getClientInformation(req.getClient()) << std::endl;
            return replyFail(req, pa::forbidden(getTimestamp(req), errorMessage));
        }

        room.players[player->name] = player;
        player->currentRoom = roomName;
        roomPtr = &room;
    }
    else {
        _server->_rooms.emplace(roomName, Room(roomName, 4));
        Room &room = _server->_rooms.at(roomName);

        room.players[player->name] = player;
        room.master = player->name;
        player->currentRoom = roomName;
        roomPtr = &room;
    }
    Room &room = *roomPtr;

    bson::Document roomInfos;

    bson::Document players;
    players << bson::Document::ARRAY_ENABLED;
    for (auto &kv : room.players) {
        std::shared_ptr<Player> &currentPlayer = kv.second;
        players << currentPlayer->name;
    }
    players << bson::Document::ARRAY_DISABLED;

    bson::Document generatorsDocument;
    generatorsDocument << bson::Document::ARRAY_ENABLED;
    std::vector<std::string> generators = this->getAvailableGenerators();
    for (const auto &generator : generators)
        generatorsDocument << generator;
    generatorsDocument << bson::Document::ARRAY_DISABLED;

    roomInfos << u8"players" << players;
    roomInfos << u8"generators" << generatorsDocument;

    logs::getLogger()[logs::SERVER] << "Has RoomJoin." << _server->getClientInformation(req.getClient()) << std::endl;
    return replyOk(req, roomInfos);
}

bool ServerRouter::RoomLeaveHandler(Request & req)
{
    // Check the integrity of the packet for the following action
    if (!protocol::client::checkRoomLeave(req.getPacket())) {
        std::string errorMessage = "The packet for the action 'RoomLeave' is not correct.";
        logs::getLogger()[logs::SERVER] << errorMessage << _server->getClientInformation(req.getClient()) << std::endl;
        return replyFail(req, pa::badRequest(-1, errorMessage));
    }

    // Check if player connected
    if (!this->isPlayerConnected(req))
        return false;
    std::shared_ptr<Player> player = _server->_players[req.getClient()];

    int64_t timestamp = getTimestamp(req);

    // Check if player is in a room
    if (!this->isPlayerInARoom(req, player))
        return false;
    Room &room = _server->_rooms.at(player->currentRoom);

    replyOk(req);

    if (player->isPlaying) {
        sendToRoomOtherPlayers(req, room, protocol::server::gameLeave(player->name));
        player->isPlaying = false;
    }
    sendToRoomPlayers(room, protocol::server::roomLeave(player->name));

    room.players.erase(player->name);
    player->currentRoom.clear();

    logs::getLogger()[logs::SERVER] << "Has RoomLeave." << _server->getClientInformation(req.getClient()) << std::endl;
    return true;
}

bool ServerRouter::RoomKickHandler(Request & req)
{
    // Check the integrity of the packet for the following action
    if (!protocol::client::checkRoomKick(req.getPacket())) {
        std::string errorMessage = "The packet for the action 'RoomKick' is not correct.";
        logs::getLogger()[logs::SERVER] << errorMessage << _server->getClientInformation(req.getClient()) << std::endl;
        return replyFail(req, pa::badRequest(-1, errorMessage));
    }

    // Check if player connected
    if (!this->isPlayerConnected(req))
        return false;
    std::shared_ptr<Player> player = _server->_players[req.getClient()];

    int64_t timestamp = getTimestamp(req);

    // Check if player is in a room
    if (!this->isPlayerInARoom(req, player))
        return false;
    Room &room = _server->_rooms.at(player->currentRoom);

    // Check if player is the room's master
    if (!this->isPlayerRoomMaster(req, player, room))
        return false;

    bson::Document const &rdata = req.getData();
    std::string targetName;

    rdata["username"] >> targetName;

    // Check if asked player is in the room
    if (!room.players.count(targetName)) {
        std::string errorMessage = "No player named '" + targetName + "' to kick.";
        logs::getLogger()[logs::SERVER] << errorMessage << _server->getClientInformation(req.getClient()) << std::endl;
        return replyFail(req, pa::notFound(getTimestamp(req), errorMessage));
    }

    // If the kicked player was playing
    std::shared_ptr<Player> &kickedPlayer = room.players.at(targetName);
    if (kickedPlayer->isPlaying) {
        sendToRoomOtherPlayers(req, room, protocol::server::gameLeave(targetName));
        kickedPlayer->isPlaying = false;
    }

    // remove player from room
    room.players.erase(targetName);

    // send ok to master
    replyOk(req);

    // send notif to all players
    sendToRoomPlayers(room, protocol::server::roomKick(targetName));

    logs::getLogger()[logs::SERVER] << "Has RoomKick." << _server->getClientInformation(req.getClient()) << std::endl;
    return true;
}

bool ServerRouter::GameStartHandler(Request & req)
{
    // Check the integrity of the packet for the following action
    if (!protocol::client::checkGameStart(req.getPacket())) {
        std::string errorMessage = "The packet for the action 'GameStart' is not correct.";
        logs::getLogger()[logs::SERVER] << errorMessage << _server->getClientInformation(req.getClient()) << std::endl;
        return replyFail(req, pa::badRequest(-1, errorMessage));
    }

    // Check if player connected
    if (!this->isPlayerConnected(req))
        return false;
    std::shared_ptr<Player> player = _server->_players[req.getClient()];

    int64_t timestamp = getTimestamp(req);

    // Check if player is in a room
    if (!this->isPlayerInARoom(req, player))
        return false;
    Room &room = _server->_rooms.at(player->currentRoom);

    // Check if player is the room's master
    if (!this->isPlayerRoomMaster(req, player, room))
        return false;

    // Check if the game is not already started or done
    if (room.game != nullptr) {
        if (!room.game->isDone()) {
            std::string errorMessage = "The game is already started.";
            logs::getLogger()[logs::SERVER] << errorMessage << _server->getClientInformation(req.getClient()) << std::endl;
            return replyFail(req, pa::forbidden(timestamp, errorMessage));
        } else {
            delete room.game;
        }
    }

    //  Check the generator name
    bson::Document const &rdata = req.getData();
    std::string generatorName = rdata["generator"].getValueString();
    this->getAvailableGenerators();
    if (!_generators.count(generatorName)) {
        std::string errorMessage = "Unknow generator '" + generatorName + "'.";
        logs::getLogger()[logs::SERVER] << errorMessage << _server->getClientInformation(req.getClient()) << std::endl;
        return replyFail(req, pa::notFound(timestamp, errorMessage));
    }

    // Get the clients tokens
    std::vector<std::string> clientsTokens;
    for (const auto &kv : room.players)
        clientsTokens.push_back(kv.second->token);

    // Launch the Game
    room.game = new Game(room, _generators.at(generatorName), _server->_serverToken, clientsTokens);
    try {
        room.game->initECS();
        room.game->launch();
    }
    catch (const std::exception &e) {
        delete room.game;
        std::string errorMessage = std::string("Error while launching the game of the room: ") + e.what();
        logs::getLogger()[logs::SERVER] << errorMessage << _server->getClientInformation(req.getClient()) << std::endl;
        return replyFail(req, pa::internalServerError(timestamp, "Can't launch the game."));
    }

    // Check the port
    int32_t port = static_cast<int32_t>(room.game->getServerUdpPort());
    if (port == -1) {
        delete room.game;
        std::string errorMessage = "Error while launching the game of the room: error with the UDP server.";
        logs::getLogger()[logs::SERVER] << errorMessage << _server->getClientInformation(req.getClient()) << std::endl;
        return replyFail(req, pa::internalServerError(timestamp, "Can't launch the game."));
    }

    // After this point, we assume that startup went well and the game is now started
    room.game->detach();
    // set players as playing
    for (auto &kv : room.players)
        kv.second->isPlaying = true;

    // Tell the clients that's everything ok
    replyOk(req);
    for (const auto &kv : room.players)
        kv.second->sock->addMessage(protocol::server::gameStart(port,
                                                                kv.second->token,
                                                                _server->_serverToken).getBufferString() +
                                    network::magic);
    logs::getLogger()[logs::SERVER] << "Has GameStart. (on port: " << static_cast<unsigned short>(port) << ")" << _server->getClientInformation(req.getClient()) << std::endl;
}

bool ServerRouter::GameLeaveHandler(Request &req)
{
    // Check the integrity of the packet for the following action
    if (!protocol::client::checkGameLeave(req.getPacket())) {
        std::string errorMessage = "The packet for the action 'GameLeave' is not correct.";
        logs::getLogger()[logs::SERVER] << errorMessage << _server->getClientInformation(req.getClient()) << std::endl;
        return replyFail(req, pa::badRequest(-1, errorMessage));
    }

    // Check if player connected
    if (!this->isPlayerConnected(req))
        return false;
    std::shared_ptr<Player> player = _server->_players[req.getClient()];

    // Check if player is in a room
    if (!this->isPlayerInARoom(req, player))
        return false;
    Room &room = _server->_rooms.at(player->currentRoom);

    // Check if Player is playing
    if (!this->isPlayerPlaying(req, player))
        return false;

    player->isPlaying = false;
    sendToRoomOtherPlayers(req, room, protocol::server::gameLeave(player->name));
    logs::getLogger()[logs::SERVER] << "Has GameLeave." << _server->getClientInformation(req.getClient()) << std::endl;
    return replyOk(req);
}

bool ServerRouter::GetAvailableRoomsHandler(Request & req)
{
    // Check the integrity of the packet for the following action
    if (!protocol::client::checkGetAvailableRooms(req.getPacket())) {
        std::string errorMessage = "The packet for the action 'GetAvailableRooms' is not correct.";
        logs::getLogger()[logs::SERVER] << errorMessage << _server->getClientInformation(req.getClient()) << std::endl;
        return replyFail(req, pa::badRequest(-1, errorMessage));
    }

    // Check if player connected
    if (!this->isPlayerConnected(req))
        return false;
    std::shared_ptr<Player> player = _server->_players[req.getClient()];

    bson::Document rooms;
    rooms << bson::Document::ARRAY_ENABLED;
    for (auto &kv : _server->_rooms) {
        Room &room = kv.second;
        bson::Document roomDocument;

        roomDocument << u8"name" << room.name;
        roomDocument << u8"master" << room.master;
        roomDocument << u8"totalSlots" << room.maximumSlots;
        roomDocument << u8"availableSlots" << static_cast<int>(room.maximumSlots - room.players.size());

        rooms << roomDocument;
    }
    rooms << bson::Document::ARRAY_DISABLED;

    logs::getLogger()[logs::SERVER] << "Has GetAvailableRooms." << _server->getClientInformation(req.getClient()) << std::endl;
    return replyOk(req, rooms);
}

bool ServerRouter::GetAvailableGenerators(Request & req) {
    // Check the integrity of the packet for the following action
    if (!protocol::client::checkGetAvailableGenerators(req.getPacket())) {
        std::string errorMessage = "The packet for the action 'GetAvailableGenerators' is not correct.";
        logs::getLogger()[logs::SERVER] << errorMessage << _server->getClientInformation(req.getClient()) << std::endl;
        return replyFail(req, pa::badRequest(-1, errorMessage));
    }

    // Check if player connected
    if (this->isPlayerConnected(req))
        return false;
    std::shared_ptr<Player> player = _server->_players[req.getClient()];

    // Get the available generators
    bson::Document generatorsDocument;
    generatorsDocument << bson::Document::ARRAY_ENABLED;
    std::vector<std::string> generators = this->getAvailableGenerators();
    for (const auto& generator : generators)
        generatorsDocument << generator;
    generatorsDocument << bson::Document::ARRAY_DISABLED;

    logs::getLogger()[logs::SERVER] << "Has GetAvailableGenerators." << _server->getClientInformation(req.getClient()) << std::endl;
    // Return the answer with the generators
    return replyOk(req, generatorsDocument);
}

int64_t ServerRouter::getTimestamp(const Request & req) const
{
    return req.getHeader()["timestamp"].getValueInt64();
}

bool ServerRouter::replyFail(Request &req, bson::Document const &message) const
{
    req.getClient()->addMessage(message.getBufferString() + network::magic);
    return false;
}

bool ServerRouter::replyOk(Request &req, bson::Document const &ok_data) const
{
    req.getClient()->addMessage(pa::ok(getTimestamp(req), ok_data).getBufferString() + network::magic);
    return true;
}

void ServerRouter::sendToRoomOtherPlayers(Request &req, Room &room, bson::Document const &broadcast_msg) const
{
    sendToRoomOtherPlayers(req.getClient(), room, broadcast_msg);
}

void ServerRouter::sendToRoomOtherPlayers(std::shared_ptr<network::ClientTCP> client, Room &room, bson::Document const &broadcast_msg) const
{
    for (auto &kv : room.players) {
        std::shared_ptr<Player> &player = kv.second;

        if (player->sock != client)
            player->sock->addMessage(broadcast_msg.getBufferString() + network::magic);
    }
}

void ServerRouter::sendToRoomPlayers(Room &room, bson::Document const &broadcast_msg) const
{
    for (auto &kv : room.players) {
        std::shared_ptr<Player> &player = kv.second;

        player->sock->addMessage(broadcast_msg.getBufferString() + network::magic);
    }
}

std::vector<std::string> ServerRouter::getAvailableGenerators() {
    std::vector<std::string> generators;
    std::string folder = "./generators/";
    FileSystemWatcher watcher(folder);

    for (const auto &i : watcher.processEvents()) {
        if (i.second == AFileSystemWatcher::Event::Add) {
            try {
                std::shared_ptr<LibraryLoader> module(new LibraryLoader(folder + i.first));
                Dependent_ptr<IGenerator, LibraryLoader> instance(module->newInstance(), module);
                _generators[instance->getName()] = instance;
            } catch (const LibraryLoaderException &e) {
                std::string errorMessage = std::string("Can't get the library name: ") + e.what();
                logs::getLogger()[logs::SERVER] << errorMessage << std::endl;
            }
        }
    }

    for (const auto& generator : _generators)
        generators.push_back(generator.first);

    return generators;
}

bool ServerRouter::isPlayerConnected(Request& request) const {
    if (!_server->_players.at(request.getClient())) {
        std::string errorMessage = "Not connected.";
        logs::getLogger()[logs::SERVER] << errorMessage << _server->getClientInformation(request.getClient()) << std::endl;
        return replyFail(request, pa::unauthorized(getTimestamp(request), errorMessage));
    }
    return true;
}

bool ServerRouter::isPlayerInARoom(Request &request, const std::shared_ptr<Player> &player) {
    if (!_server->_rooms.count(player->currentRoom)) {
        std::string errorMessage = "Not in any room.";
        logs::getLogger()[logs::SERVER] << errorMessage << _server->getClientInformation(request.getClient()) << std::endl;
        return replyFail(request, pa::forbidden(getTimestamp(request), errorMessage));
    }
    return true;
}

bool ServerRouter::isPlayerRoomMaster(Request &request, const std::shared_ptr<Player> &player, const Room &room) {
    if (room.master != player->name) {
        std::string errorMessage = "You are not the room's master.";
        logs::getLogger()[logs::SERVER] << errorMessage << _server->getClientInformation(request.getClient()) << std::endl;
        return replyFail(request, pa::forbidden(getTimestamp(request), errorMessage));
    }
    return true;
}

bool ServerRouter::isPlayerPlaying(Request &request, const std::shared_ptr<Player> &player) {
    if (!player->isPlaying) {
        std::string errorMessage = "Not playing.";
        logs::getLogger()[logs::SERVER] << errorMessage << _server->getClientInformation(request.getClient()) << std::endl;
        return replyFail(request, pa::forbidden(getTimestamp(request), errorMessage));
    }
    return true;
}
