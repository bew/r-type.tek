/**
 * @file Router.cpp
 * @author Benoit de Chezelles
 * @brief Implementation for the Router
 */

#include "Router.hpp"

//== Request implementation =================================================

Request::Request(bson::Document const & packet, std::shared_ptr<network::ClientTCP> fromClient) :
  _client(fromClient),
  _header(packet["header"].getValueDocument()),
  _data(packet["data"].getValueDocument())
{}

Request::~Request()
{}

bson::Document const & Request::getHeader() const
{
  return _header;
}

bson::Document const & Request::getData() const
{
  return _data;
}

std::shared_ptr<network::ClientTCP> Request::getClient() const
{
  return _client;
}

//== Router implementation ==================================================

Router::Router() :
  _handlers(),
  _fallbackHandler()
{}

Router::Router(Router const & other)
{
  *this = other;
}

Router & Router::operator=(Router const & other)
{
  if (this != &other) {
    _handlers = other._handlers;
    _fallbackHandler = other._fallbackHandler;
  }
  return *this;
}

Router::~Router()
{}

void Router::addRoute(std::string const & route, RouteHandler handler)
{
  _handlers[route] = handler;
}

void Router::setFallbackHandler(RouteHandler handler)
{
  _fallbackHandler = handler;
}

Router::RouteHandler::result_type Router::routePacket(bson::Document const & packet, std::shared_ptr<network::ClientTCP> fromClient) const
{
  Request req(packet, fromClient);

  auto & header = req.getHeader();
  std::string action;

  header["action"] >> action;

  if (!_handlers.count(action))
    {
      if (_fallbackHandler)
	return _fallbackHandler(req);
      else
	throw NoRouteException("No route for action '" + action + "'");
    }

  RouteHandler const & handler = _handlers.at(action);
  return handler(req);
}

