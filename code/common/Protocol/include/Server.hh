/**
 * @file Server.hh
 * @brief serialize messages server into BSON for R-Type protocol
 * @author Christopher Paccard
 *
 * Functions to serialize messages server into BSON for the R-Type protocol
 *
 */

#ifndef PROTOCOL_SERVER_HH
#define PROTOCOL_SERVER_HH

#include "Protocol.hh"

/**
 * Contain all functions to use for the R-Type protocol
 */
namespace protocol {
    /**
     * Contain all functions to use for server in R-Type protocol
     */
    namespace server {
        /**
         * Create a message to notify all the other players that a player joined the room
         *
         * @param id the id of who send the message
         * @param username the username of the player that joined the room
         * @return the bson Document formatted for the following action
         */
        bson::Document roomJoin(const std::string& id, const std::string& username);

        /**
         * Create a message to notify all the other players that a player leaved the room
         *
         * @param id the id of who send the message
         * @param username the username of the player that leaved the room
         * @return the bson Document formatted for the following action
         */
        bson::Document roomLeave(const std::string& id, const std::string& username);

        /**
         * Create a message to notify all the other players that a player has been kicked from the room
         *
         * @param id the id of who send the message
         * @param username the username of the player that has been kicked from the room
         * @return the bson Document formatted for the following action
         */
        bson::Document roomKick(const std::string& id, const std::string& username);

        /**
         * Create a message to notify all the players that the game has started
         *
         * @param id the id of who send the message
         * @return the bson Document formatted for the following action
         */
        bson::Document gameStart(const std::string& id);

        /**
         * Create a message to notify all the other players that a player has been leaved the game
         *
         * @param id the id of who send the message
         * @param username the username of the player that leaved the game
         * @return the bson Document formatted for the following action
         */
        bson::Document gameLeave(const std::string& id, const std::string& username);

        /**
         * Create a message to update an entity to a client
         *
         * @param id the id of who send the message
         * @param entity_id the id of the entity to update
         * @param component the component to update
         * @param data the data to update
         * @return the bson Document formatted for the following action
         */
        bson::Document entityUpdate(const std::string& id, int64_t entity_id, const std::string& component, const bson::Document& data);
    }
}

#endif //PROJECT_SERVER_HH
