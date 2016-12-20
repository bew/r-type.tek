/**
 * @file Client.hh
 * @brief serialize messages client into BSON for R-Type protocol
 * @author Christopher Paccard
 *
 * Functions to serialize messages client into BSON for the R-Type protocol
 *
 */

#ifndef PROTOCOL_CLIENT_HH
#define PROTOCOL_CLIENT_HH

#include "Protocol.hh"

/**
 * Contain all functions to use for the R-Type protocol
 */
namespace protocol {
    /**
     * Contain all functions to use for client in R-Type protocol
     */
    namespace client {
        /**
         * Create a message to register a player on the server
         *
         * @param username the username of the player who register
         * @param password the password of the player who register
         * @return the bson Document formatted for the following action
         */
        bson::Document signUp(const std::string& username, const std::string& password);

        /**
         * Create a message to login a player on the server
         *
         * @param username the username of the player who login
         * @param password the password of the player who login
         * @return the bson Document formatted for the following action
         */
        bson::Document login(const std::string& username, const std::string& password);

        /**
         * Create a message to logout a player on the server
         *
         * @param username the username of the player who logout
         * @param password the password of the player who logout
         * @return the bson Document formatted for the following action
         */
        bson::Document logout(const std::string& username, const std::string& password);

        /**
         * Create a message in order to create a room with a optional password
         *
         * @param name the name of the room
         * @param password the password of the room
         * @return the bson Document formatted for the following action
         */
        bson::Document roomJoin(const std::string& name, const std::string& password = "");

        /**
         * Create a message in order to leave a room
         *
         * @return the bson Document formatted for the following action
         */
        bson::Document roomLeave(void);

        /**
         * Create a message in order to kick a player of the room
         *
         * @param username the username of the player to kick
         * @return the bson Document formatted for the following action
         */
        bson::Document roomKick(const std::string& username);

        /**
         * Create a message in order to start the game
         *
         * @return the bson Document formatted for the following action
         */
        bson::Document gameStart(void);

        /**
         * Create a message in order to leave the game
         *
         * @return the bson Document formatted for the following action
         */
        bson::Document gameLeave(void);

        /**
         * Create a message to update an entity to a client
         *
         * @param entity_id the id of the entity to update
         * @param components a Document of components to update
         * @return the bson Document formatted for the following action
         */
        bson::Document entityUpdate(int64_t entity_id, const bson::Document& components);
    }
}

#endif //PROJECT_CLIENT_HH
