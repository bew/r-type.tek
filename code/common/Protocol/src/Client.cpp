/**
 * @file Client.cpp
 * @brief serialize messages client into BSON for R-Type protocol
 * @author Christopher Paccard
 *
 * Functions to serialize messages client into BSON for the R-Type protocol
 *
 */

#include "Client.hh"

namespace protocol {
    namespace client {
        bson::Document signUp(const std::string& username, const std::string& password) {
            bson::Document document;

            bson::Document message;

            message << u8"username" << username;
            message << u8"password" << password;

            document << u8"header" << protocol::createHeader("signUp");
            document << u8"data" << message;

            return document;
        }

        bson::Document login(const std::string& username, const std::string& password) {
            bson::Document document;

            bson::Document message;

            message << u8"username" << username;
            message << u8"password" << password;

            document << u8"header" << protocol::createHeader("Login");
            document << u8"data" << message;

            return document;
        }

        bson::Document logout(const std::string& username, const std::string& password) {
            bson::Document document;

            bson::Document message;

            message << u8"username" << username;
            message << u8"password" << password;

            document << u8"header" << protocol::createHeader("Logout");
            document << u8"data" << message;

            return document;
        }

        bson::Document roomJoin(const std::string& name, const std::string& password) {
            bson::Document document;
            bson::Document message;

            message << u8"name" << name;
            message << u8"password" << password;

            document << u8"header" << protocol::createHeader("RoomJoin");
            document << u8"data" << message;

            return document;
        }

        bson::Document roomLeave(void) {
            bson::Document document;
            bson::Document message;

            document << u8"header" << protocol::createHeader("RoomLeave");
            document << u8"data" << message;

            return document;
        }

        bson::Document roomKick(const std::string& username) {
            bson::Document document;
            bson::Document message;

            message << u8"username" << username;

            document << u8"header" << protocol::createHeader("RoomKick");
            document << u8"data" << message;

            return document;
        }

        bson::Document gameStart(void) {
            bson::Document document;
            bson::Document message;

            document << u8"header" << protocol::createHeader("GameStart");
            document << u8"data" << message;

            return document;
        }

        bson::Document gameLeave(void) {
            bson::Document document;
            bson::Document message;

            document << u8"header" << protocol::createHeader("GameLeave");
            document << u8"data" << message;

            return document;
        }

        bson::Document entityUpdate(int64_t entity_id, const std::string& component, const bson::Document& data) {
            bson::Document document;
            bson::Document message;

            message << u8"entity_id" << entity_id;
            message << u8"component" << component;
            message << u8"data" << data;

            document << u8"header" << protocol::createHeader("EntityUpdate");
            document << u8"data" << message;

            return document;
        }

    }
}