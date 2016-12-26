/**
 * @file Router.hpp
 * @author Benoit de Chezelles
 * @brief Class for the Router
 */

#ifndef ROUTER_HPP_
# define ROUTER_HPP_

# include <string>
# include <map>
# include <functional>
# include "BSON/Document.hh"
# include "Server.hpp"

/**
 * Represent a request
 */
class Request
{
public:
  /**
   * Construct a request from a BSON packet
   */
  Request(bson::Document const & packet);

  /**
   * Destructor of a request
   */
  ~Request();

  Request(Request const & other) = delete;
  Request & operator=(Request const & other) = delete;

public:
  /**
   * Get the header of the request
   *
   * @return a document to the header of the packet
   */
  bson::Document const & getHeader() const;

  /**
   * Get the data of the request
   *
   * @return a document to the data of the packet
   */
  bson::Document const & getData() const;

protected:
  /**
   * Store a reference to the packet
   */
  bson::Document const & _packet;

  /**
   * Store a reference to the packet header
   */
  bson::Document const & _header;

  /**
   * Store a reference to the packet data
   */
  bson::Document const & _data;
};

/**
 * Represent a router, it re-route a network packet to the right handler
 */
class Router
{
public:
  /**
   * Type representation for a route handler
   */
  typedef std::function<void(Request &)> RouteHandler;

public:
  /**
   * Constructor of a Router
   */
  Router();

  /**
   * Copy constructor
   *
   * @param other The other Router to copy from
   */
  Router(Router const & other);

  /**
   * Copy by assignement
   * @param other The other Router to copy from
   * @return a reference to this Router
   */
  Router & operator=(Router const & other);

  /**
   * Destructor of a Router
   */
  ~Router();

public:
  /**
   * Add a route to the list of handled routes by this router
   *
   * @param route The name of the route
   * @param handler The function which will handle this route
   */
  void addRoute(std::string const & route, RouteHandler handler);

  /**
   * Given a packet, re-route the packet to the correct handler
   *
   * @param packet The packet to re-route
   */
  void routePacket(bson::Document const & packet) const;

  /**
   * Set the fallback handler when no route match the packet request
   *
   * @param handler The function to use as route fallback
   */
  void setFallbackHandler(RouteHandler handler);

protected:
  /**
   * Store the handlers for each routes
   */
  std::map<std::string, RouteHandler> _handlers;

  /**
   * Store the fallback handler
   */
  RouteHandler _fallbackHandler;
};



#endif /* !ROUTER_HPP_ */
