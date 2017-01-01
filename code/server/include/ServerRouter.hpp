/**
 * @file ServerRouter.cpp
 * @author Benoit de Chezelles
 * @brief Implementation for the ServerRouter
 */

#pragma once

class ServerRouter;

class Server;

#include "Protocol/Answers.hh"
#include "Router.hpp"
#include "Room.hpp"

/**
 * Represent the Server command router and handler
 */
class ServerRouter : public Router {
private:
    typedef bool (handler_t)(Request &);

    handler_t SignUpHandler, LoginHandler, LogoutHandler;
    handler_t RoomJoinHandler, RoomLeaveHandler, RoomKickHandler;
    handler_t GameStartHandler, GameLeaveHandler;
    handler_t GetAvailableRoomsHandler, GetAvailableGenerators;

public:
    /**
     * Construct a ServerRouter, which has full access to the given server
     *
     * @param server The associated server
     */
    ServerRouter(Server &server);

protected:
    /**
     * Extract the timestamp from a Request
     *
     * @param req The request to extract from
     * @return The timestamp
     */
    int64_t getTimestamp(const Request &req) const;

    /**
     * Reply the given document to the request sender
     *
     * @param req The request to respond to
     * @param message The Document full of error explaination
     * @return false
     */
    bool replyFail(Request &req, bson::Document const &message) const;

    /**
     * Reply a successfull answer to the request sender, with
     * additional data if needed
     *
     * @param req The request to respond to
     * @param ok_data Additional data for the response
     * @return true
     */
    bool replyOk(Request &req, bson::Document const &ok_data = bson::Document()) const;

    /**
     * Send a command to all players of a Room except the sender
     *
     * @param req The request, used to get the sender
     * @param room The room
     * @param broadcast_msg The command to send
     */
    void sendToRoomOtherPlayers(Request &req, Room &room, bson::Document const &broadcast_msg) const;

    /**
     * Send a command to all players of a Room
     *
     * @param room The room
     * @param broadcast_msg The command to send
     */
    void sendToRoomPlayers(Room &room, bson::Document const &broadcast_msg) const;

    /**
     * Allow to get the list of all available generators on the server
     *
     * @return the list of all available generators on the server
     */
    std::vector<std::string> getAvailableGenerators(void) const;

    /**
     * Allow to check if a Player is connected
     * If not, send the correct message
     *
     * @param request The request, used to get the client
     * @return true if it's connected, else false
     */
    bool isPlayerConnected(Request &request) const;

protected:
    /**
     * Pointer on the server
     */
    Server *_server;
};
