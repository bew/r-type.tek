/**
 * @file Router.cpp
 * @author Benoit de Chezelles
 * @brief Implementation for the Router
 */

#include "Router.hpp"

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

  auto header = req.getHeader();
  std::string action;

  header["action"] >> action;

  if (!_handlers.count(action) && _fallbackHandler)
    {
      _fallbackHandler(req);
      return;
    }

  RouteHandler handler = _handlers.at(action);
  handler(req);
}

