/**
 * @file Server.cpp
 * @author Benoit de Chezelles
 * @brief Implementation for the server
 */

#include <iostream>
#include <algorithm>

#include "BSON/Document.hh"
#include "Protocol/Answers.hh"
#include "Network/SocketException.hh"
#include "Logs/Logger.hh"
#include "ServerLogLevel.hh"
#include "Server.hpp"

const std::string Server::SERVER_TOKEN = "Jarvis";
const unsigned short Server::PORT = 42403;

Server::Server(std::string const & token) :
  _serverToken(token),
  _router(*this)
{}

Server::~Server()
{}

unsigned short Server::initNetwork(unsigned short port)
{
  network::SockAddr addr(port);
  try
    {
      _serverSock.bind(addr);
      _serverSock.listen();
    }
  catch (network::SocketException const & e)
    {
      logs::getLogger()[logs::ERRORS] << "Init network error: " << e.what() << std::endl;
      return 0;
    }
  return addr.getPort();
}

void Server::run()
{
    while (true)
    {
        _serverSock.update();
        processNewClients();
        processDisconnectedClients();

        std::shared_ptr<network::ClientTCP> cl = _serverSock.getFirstClientWithMessage();
        while (cl)
        {
            processMessage(cl);
            cl = _serverSock.getFirstClientWithMessage();
        }
    }
}

void Server::processMessage(std::shared_ptr<network::ClientTCP> client)
{
    std::string const &raw_packet = client->getMessage();

    // Try to unserialize the packet
    bson::Document packet;
    try {
        packet = bson::Document(raw_packet);
    }
    catch (const bson::BsonException &e) {
        client->addMessage(protocol::answers::badRequest(-1, "Can't deserialize packet").getBufferString() + network::magic);
        logs::getLogger()[logs::SERVER] << "Received a packet but can't deserialize it. " << e.what() << " " << this->getClientInformation(client) << std::endl;
        return;
    }

    // Check the integrity of the packet received
    if (!protocol::checkMessage(packet)) {
        client->addMessage(protocol::answers::badRequest(-1, "Wrong packet format").getBufferString() + network::magic);
        logs::getLogger()[logs::SERVER] << "Received a packet but wrong format : " << packet.toJSON(2) << std::endl << this->getClientInformation(client) << std::endl;
        return;
    }
    else
        logs::getLogger()[logs::SERVER] << "Received a valid packet :" << std::endl << packet.toJSON(2) << std::endl << this->getClientInformation(client) << std::endl;

    bson::Document const &header = packet["header"].getValueDocument();
    int64_t timestamp = header["timestamp"].getValueInt64();
    std::string action = header["action"].getValueString();

    ClientCommandsState &state = _players.at(client)->controlState;

    logs::getLogger()[logs::SERVER] << "Client " << client << " " << this->getClientInformation(client)
                                    << " try action '" << action
                                    << "' current state is '" << state.getCurrentState()->getName() << "'" << std::endl;

    if (!state.gotoNextStateVia(action)) {
        logs::getLogger()[logs::SERVER] << "Unauthorized action '" << action << "' " << this->getClientInformation(client) << std::endl;
        client->addMessage(protocol::answers::unauthorized(timestamp).getBufferString() + network::magic);
        return;
    }

    if (!_router.routePacket(packet, client)) {
        state.revertToPreviousState();
        return;
    }
    logs::getLogger()[logs::SERVER] << "Client state is now '" << state.getCurrentState()->getName() << "' " << this->getClientInformation(client)
                                    << std::endl;
}

std::string Server::getClientInformation(const std::shared_ptr<network::ClientTCP> client) {
    std::string ip;
    unsigned short port;
    client->getSocket().getInfos(network::ASocketTCP::PEER, ip, port);

    return std::string("(ip: " + ip + ", port: " + std::to_string(port) + ")");
}

void Server::processNewClients()
{
    for (auto & client : _serverSock.getConnections())
    {
        if (_players.count(client))
            continue;

        _players[client] = std::make_shared<Player>(client);
        logs::getLogger()[logs::SERVER] << "New client connected (at:" << client << ") " << this->getClientInformation(client) << std::endl;
    }
}

void Server::processDisconnectedClients()
{
    std::vector<std::shared_ptr<network::ClientTCP>> const & stillConnected = _serverSock.getConnections();

    if (_players.size() == 0 || _players.size() == stillConnected.size())
        return;

    std::vector<std::shared_ptr<network::ClientTCP>> disClients;

    // fill with known clients
    for (auto & client : stillConnected)
        disClients.push_back(kv.first);

    // remove all still connected clients
    disClients.erase(std::remove_if(disClients.begin(), disClients.end(), [&](std::shared_ptr<network::ClientTCP> const & client) {
                                    return std::find(stillConnected.begin(), stillConnected.end(), client) != stillConnected.end();
                                 }));

    for (auto & client : disClients)
        disconnectClient(client, true);
}

void Server::disconnectClient(std::shared_ptr<network::ClientTCP> client, bool sendOther)
{
    std::shared_ptr<Player> player = _players.at(client);

    if (!player->currentRoom.empty() && _rooms.count(player->currentRoom)) {
        Room & room = _rooms.at(player->currentRoom);
        if (player->isPlaying) {
            if (sendOther)
                _router.sendToRoomOtherPlayers(client, room, protocol::server::gameLeave(player->name));
            player->isPlaying = false;
        }
        if (sendOther)
            _router.sendToRoomOtherPlayers(client, room, protocol::server::roomLeave(player->name));

        room.players.erase(player->name);
        player->currentRoom.clear();
    }

    _players.erase(client);
    if (! player->name.empty())
    {
        _players_by_name.erase(player->name);
        logs::getLogger()[logs::SERVER] << "Player '" << player->name << "' force disconnected" << std::endl;
    }
    else
        logs::getLogger()[logs::SERVER] << "Anonymous player force disconnected" << std::endl;

}
