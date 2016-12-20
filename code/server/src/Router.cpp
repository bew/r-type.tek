/**
 * @file Router.cpp
 * @author Benoit de Chezelles
 * @brief Implementation for the Router
 */

#include "Router.hpp"

//== Request implementation =================================================

Request::Request(bson::Document const & packet) :
  _packet(packet),
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

//== Router implementation ==================================================

Router::Router() :
  _handlers(),
  _fallbackHandler()
{}

Router::Router(Router const & other) :
  _handlers(other._handlers),
  _fallbackHandler(other._fallbackHandler)
{}

Router & Router::operator=(Router const & other)
{
  _handlers = other._handlers;
  _fallbackHandler = other._fallbackHandler;
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

void Router::routePacket(bson::Document const & packet) const
{
  Request req(packet);

  auto & header = req.getHeader();
  std::string action;

  header["action"] >> action;

  if (!_handlers.count(action))
    {
      if (_fallbackHandler)
	_fallbackHandler(req);
      return;
    }

  RouteHandler handler = _handlers.at(action);
  handler(req);
}

