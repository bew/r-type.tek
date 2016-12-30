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
         * @param username the username of the player that joined the room
         * @return the bson Document formatted for the following action
         */
        bson::Document roomJoin(const std::string &username);

        /**
         * Check if the given Document is a correct roomJoin message
         *
         * @param document the Document to check
         * @return true if the Document is correct, else false
         */
        bool checkRoomJoin(const bson::Document &document);

        /**
         * Create a message to notify all the other players that a player leaved the room
         *
         * @param username the username of the player that leaved the room
         * @return the bson Document formatted for the following action
         */
        bson::Document roomLeave(const std::string &username);

        /**
         * Check if the given Document is a correct roomLeave message
         *
         * @param document the Document to check
         * @return true if the Document is correct, else false
         */
        bool checkRoomLeave(const bson::Document &document);

        /**
         * Create a message to notify all the other players that a player has been kicked from the room
         *
         * @param username the username of the player that has been kicked from the room
         * @return the bson Document formatted for the following action
         */
        bson::Document roomKick(const std::string &username);

        /**
         * Check if the given Document is a correct roomKick message
         *
         * @param document the Document to check
         * @return true if the Document is correct, else false
         */
        bool checkRoomKick(const bson::Document &document);

        /**
         * Create a message to notify all the players that the game has started
         *
         * @param token the token that the client need to sent back when opening UDP connection for the game
         * @return the bson Document formatted for the following action
         */
        bson::Document gameStart(const std::string &token);

        /**
         * Check if the given Document is a correct gameStart message
         *
         * @param document the Document to check
         * @return true if the Document is correct, else false
         */
        bool checkGameStart(const bson::Document &document);

        /**
         * Create a message to notify all the other players that a player has been leaved the game
         *
         * @param username the username of the player that leaved the game
         * @return the bson Document formatted for the following action
         */
        bson::Document gameLeave(const std::string &username);

        /**
         * Check if the given Document is a correct gameLeave message
         *
         * @param document the Document to check
         * @return true if the Document is correct, else false
         */
        bool checkGameLeave(const bson::Document &document);

        /**
         * Create a message to update an entity to a client
         *
         * @param entity_id the id of the entity to update
         * @param components a Document of components to update
         * @return the bson Document formatted for the following action
         */
        bson::Document entityUpdate(int64_t entity_id, const bson::Document &components);

        /**
         * Check if the given Document is a correct entityUpdate message
         *
         * @param document the Document to check
         * @return true if the Document is correct, else false
         */
        bool checkEntityUpdate(const bson::Document &document);
    }
}

#endif //PROJECT_SERVER_HH
