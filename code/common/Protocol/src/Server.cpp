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

        bool checkRoomJoin(const bson::Document &document) {
            return document.elementsCount() == 1 &&
                   protocol::checkString(document, "username");
        }

        bson::Document roomLeave(const std::string& username) {
            bson::Document document;
            bson::Document message;

            message << u8"username" << username;

            document << u8"header" << protocol::createHeader("RoomLeave");
            document << u8"data" << message;

            return document;
        }

        bool checkRoomLeave(const bson::Document &document) {
            return document.elementsCount() == 1 &&
                   protocol::checkString(document, "username");
        }

        bson::Document roomKick(const std::string& username) {
            bson::Document document;
            bson::Document message;

            message << u8"username" << username;

            document << u8"header" << protocol::createHeader("RoomKick");
            document << u8"data" << message;

            return document;
        }

        bool checkRoomKick(const bson::Document &document) {
            return document.elementsCount() == 1 &&
                   protocol::checkString(document, "username");
        }

        bson::Document gameStart(void) {
            bson::Document document;
            bson::Document message;

            document << u8"header" << protocol::createHeader("GameStart");
            document << u8"data" << message;

            return document;
        }

        bool checkGameStart(const bson::Document &document) {
            return !document.elementsCount();
        }

        bson::Document gameLeave(const std::string& username) {
            bson::Document document;
            bson::Document message;

            message << u8"username" << username;

            document << u8"header" << protocol::createHeader("GameLeave");
            document << u8"data" << message;

            return document;
        }

        bool checkGameLeave(const bson::Document &document) {
            return document.elementsCount() == 1 &&
                   protocol::checkString(document, "username");
        }

        bson::Document entityUpdate(int64_t entity_id, const bson::Document& components) {
            bson::Document document;
            bson::Document message;

            message << u8"entity_id" << entity_id;
            message << u8"components" << components;

            document << u8"header" << protocol::createHeader("EntityUpdate");
            document << u8"data" << message;

            return document;
        }

    }
}