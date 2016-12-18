/**
 * @file Server.cpp
 * @brief serialize messages server into BSON for R-Type protocol
 * @author Christopher Paccard
 *
 * Functions to serialize messages server into BSON for the R-Type protocol
 *
 */

#include "Server.hh"

namespace protocol {
    namespace server {
        bson::Document roomJoin(const std::string& username) {
            bson::Document document;
            bson::Document message;

            message << u8"username" << username;

            document << u8"header" << protocol::createHeader("RoomJoin");
            document << u8"data" << message;

            return document;
        }

        bson::Document roomLeave(const std::string& username) {
            bson::Document document;
            bson::Document message;

            message << u8"username" << username;

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

        bson::Document gameLeave(const std::string& username) {
            bson::Document document;
            bson::Document message;

            message << u8"username" << username;

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