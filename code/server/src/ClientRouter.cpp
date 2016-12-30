/**
 * @file ClientRouter.cpp
 * @author Benoit de Chezelles
 * @brief Implementation for the ClientRouter
 */

#include "ClientRouter.hpp"
#include "Logs/Logger.hh"
#include "ServerLogLevel.hh"

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
  bson::Document const & rpacket = req.getPacket();
  if (protocol::client::checkSignUp(rpacket)) {
    std::string errorMessage = "The packet for the action 'SignUp' is not correct.";
    req.getClient()->addMessage(protocol::answers::badRequest(this->getTimestamp(req), errorMessage).getBufferString() + network::magic);
    logs::logger[logs::SERVER] << errorMessage << std::endl;
    return false;
  }

  bson::Document const & rdata = req.getData();

  std::string username, password;

  rdata["username"] >> username;
  rdata["password"] >> password;

  if (_server->_accounts.count(username))
    {
      auto const & answer = protocol::answers::badRequest(getTimestamp(req), "Username " + username + " already taken.");
      req.getClient()->addMessage(answer.getBufferString() + network::magic);
      return false;
    }

  _server->_accounts[username] = std::make_shared<Account>(username, password);

  auto const & answer = protocol::answers::ok(getTimestamp(req));
  req.getClient()->addMessage(answer.getBufferString() + network::magic);
  return true;
}

bool ClientRouter::LoginHandler(Request & req)
{
  bson::Document const & rpacket = req.getPacket();
  if (protocol::client::checkLogin(rpacket)) {
    std::string errorMessage = "The packet for the action 'Login' is not correct.";
    req.getClient()->addMessage(protocol::answers::badRequest(this->getTimestamp(req), errorMessage).getBufferString() + network::magic);
    logs::logger[logs::SERVER] << errorMessage << std::endl;
    return false;
  }

  bson::Document const & rdata = req.getData();

  std::string username, password;

  rdata["username"] >> username;
  rdata["password"] >> password;

  if (!_server->_accounts.count(username))
    {
      auto const & answer = protocol::answers::unauthorized(this->getTimestamp(req), "Unknown username/password");
      req.getClient()->addMessage(answer.getBufferString() + network::magic);
      return false;
    }

  std::shared_ptr<Account> const account = _server->_accounts.at(username);
  if (! (account->getPassword() == password))
    {
      auto const & answer = protocol::answers::unauthorized(getTimestamp(req), "Unknown username/password");
      req.getClient()->addMessage(answer.getBufferString() + network::magic);
      return false;
    }

  auto const & answer = protocol::answers::ok(getTimestamp(req));
  req.getClient()->addMessage(answer.getBufferString() + network::magic);
  return true;
}

bool ClientRouter::LogoutHandler(Request &req)
{
  bson::Document const & rpacket = req.getPacket();
  if (protocol::client::checkLogout(rpacket)) {
    std::string errorMessage = "The packet for the action 'Logout' is not correct.";
    req.getClient()->addMessage(protocol::answers::badRequest(this->getTimestamp(req), errorMessage).getBufferString() + network::magic);
    logs::logger[logs::SERVER] << errorMessage << std::endl;
    return false;
  }

  bson::Document const & rdata = req.getData();

  // send to other players : (cumulative message ?)
  // if client was in game => send game leave
  // if client was in room => send room leave

  return true;
}

bool ClientRouter::RoomLeaveHandler(Request &req)
{
  bson::Document const & rpacket = req.getPacket();
  if (protocol::client::checkRoomLeave(rpacket)) {
    std::string errorMessage = "The packet for the action 'RoomLeave' is not correct.";
    req.getClient()->addMessage(protocol::answers::badRequest(this->getTimestamp(req), errorMessage).getBufferString() + network::magic);
    logs::logger[logs::SERVER] << errorMessage << std::endl;
    return false;
  }

  bson::Document const & rdata = req.getData();

  // send to other players

  return true;
}

bool ClientRouter::RoomKickHandler(Request &req)
{
  bson::Document const & rpacket = req.getPacket();
  if (protocol::client::checkRoomKick(rpacket)) {
    std::string errorMessage = "The packet for the action 'RoomKick' is not correct.";
    req.getClient()->addMessage(protocol::answers::badRequest(this->getTimestamp(req), errorMessage).getBufferString() + network::magic);
    logs::logger[logs::SERVER] << errorMessage << std::endl;
    return false;
  }

  bson::Document const & rdata = req.getData();

  // send to targeted player
  // remove player from room

  // send to other players

  return true;
}

bool ClientRouter::GameStartHandler(Request &req)
{
  bson::Document const & rpacket = req.getPacket();
  if (protocol::client::checkGameStart(rpacket)) {
    std::string errorMessage = "The packet for the action 'GameStart' is not correct.";
    req.getClient()->addMessage(protocol::answers::badRequest(this->getTimestamp(req), errorMessage).getBufferString() + network::magic);
    logs::logger[logs::SERVER] << errorMessage << std::endl;
    return false;
  }

  bson::Document const & rdata = req.getData();

  // prepare thread
  // prepare ECS ...

  // open UDP data socket

  // choose network token for players
  // send to other players + auth token
  // FIXME: more ?

  return true;
}

bool ClientRouter::GameLeaveHandler(Request &req)
{
  bson::Document const & rpacket = req.getPacket();
  if (protocol::client::checkGameLeave(rpacket)) {
    std::string errorMessage = "The packet for the action 'GameLeave' is not correct.";
    req.getClient()->addMessage(protocol::answers::badRequest(this->getTimestamp(req), errorMessage).getBufferString() + network::magic);
    logs::logger[logs::SERVER] << errorMessage << std::endl;
    return false;
  }

  bson::Document const & rdata = req.getData();

  // send to other players

  return true;
}

int64_t ClientRouter::getTimestamp(Request & req) const
{
  return req.getHeader()["timestamp"].getValueInt64();
}
