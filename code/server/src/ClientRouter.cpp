/**
 * @file ClientRouter.cpp
 * @author Benoit de Chezelles
 * @brief Implementation for the ClientRouter
 */

#pragma once

#include "ClientRouter.hpp"

ClientRouter::ClientRouter(Server & server) :
  _server(server)
{
  this->addRoute("SignUp",    std::bind(&ClientRouter::SignUpHandler, this, std::placeholders::_1));
  this->addRoute("Login",     std::bind(&ClientRouter::LoginHandler, this, std::placeholders::_1));
  this->addRoute("Logout",    std::bind(&ClientRouter::LogoutHandler, this, std::placeholders::_1));
  this->addRoute("RoomLeave", std::bind(&ClientRouter::RoomLeaveHandler, this, std::placeholders::_1));
  this->addRoute("RoomKick",  std::bind(&ClientRouter::RoomKickHandler, this, std::placeholders::_1));
  this->addRoute("GameStart", std::bind(&ClientRouter::GameStartHandler, this, std::placeholders::_1));
  this->addRoute("GameLeave", std::bind(&ClientRouter::GameLeaveHandler, this, std::placeholders::_1));
}

bool ClientRouter::SignUpHandler(Request & req)
{
  bson::Document const & rdata = req.getData();
  std::string username, password;

  rdata["username"] >> username;
  rdata["password"] >> password;


}

bool ClientRouter::LoginHandler(Request &)
{
}

bool ClientRouter::LogoutHandler(Request &)
{
}

bool ClientRouter::RoomLeaveHandler(Request &)
{
}

bool ClientRouter::RoomKickHandler(Request &)
{
}

bool ClientRouter::GameStartHandler(Request &)
{
}

bool ClientRouter::GameLeaveHandler(Request &)
{
}

protected:
Server & _server;
};

