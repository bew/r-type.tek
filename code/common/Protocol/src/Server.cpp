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
        bson::Document roomJoin(const std::string &username) {
            bson::Document document;
            bson::Document message;

            message << u8"username" << username;

            document << u8"header" << protocol::createHeader("RoomJoin");
            document << u8"data" << message;

            return document;
        }

        bool checkRoomJoin(const bson::Document &document) {
            if (!protocol::checkMessage(document) ||
                document[u8"header"][u8"action"].getValueString() != u8"RoomJoin")
                return false;
            bson::Document data = document[u8"data"].getValueDocument();
            return data.elementsCount() == 1 &&
                   protocol::checkString(data, "username");
        }

        bson::Document roomLeave(const std::string &username) {
            bson::Document document;
            bson::Document message;

            message << u8"username" << username;

            document << u8"header" << protocol::createHeader("RoomLeave");
            document << u8"data" << message;

            return document;
        }

        bool checkRoomLeave(const bson::Document &document) {
            if (!protocol::checkMessage(document) ||
                document[u8"header"][u8"action"].getValueString() != u8"RoomLeave")
                return false;
            bson::Document data = document[u8"data"].getValueDocument();
            return data.elementsCount() == 1 &&
                   protocol::checkString(data, "username");
        }

        bson::Document roomKick(const std::string &username) {
            bson::Document document;
            bson::Document message;

            message << u8"username" << username;

            document << u8"header" << protocol::createHeader("RoomKick");
            document << u8"data" << message;

            return document;
        }

        bool checkRoomKick(const bson::Document &document) {
            if (!protocol::checkMessage(document) ||
                document[u8"header"][u8"action"].getValueString() != u8"RoomKick")
                return false;
            bson::Document data = document[u8"data"].getValueDocument();
            return data.elementsCount() == 1 &&
                   protocol::checkString(data, "username");
        }

        bson::Document gameStart(int32_t port, const std::string& clientToken, const std::string& serverToken) {
            bson::Document document;
            bson::Document message;

            message << u8"port" << port;
            message << u8"clientToken" << clientToken;
            message << u8"serverToken" << serverToken;

            document << u8"header" << protocol::createHeader("GameStart");
            document << u8"data" << message;

            return document;
        }

        bool checkGameStart(const bson::Document &document) {
            if (!protocol::checkMessage(document) ||
                document[u8"header"][u8"action"].getValueString() != u8"GameStart")
                return false;
            bson::Document data = document[u8"data"].getValueDocument();
            return data.elementsCount() == 3 &&
                   data.hasKey(u8"port") && data[u8"port"].getValueType() == bson::INT32 &&
                   protocol::checkString(data, u8"clientToken") &&
                   protocol::checkString(data, u8"serverToken");
        }

        bson::Document gameLeave(const std::string &username) {
            bson::Document document;
            bson::Document message;

            message << u8"username" << username;

            document << u8"header" << protocol::createHeader("GameLeave");
            document << u8"data" << message;

            return document;
        }

        bool checkGameLeave(const bson::Document &document) {
            if (!protocol::checkMessage(document) ||
                document[u8"header"][u8"action"].getValueString() != u8"GameLeave")
                return false;
            bson::Document data = document[u8"data"].getValueDocument();
            return data.elementsCount() == 1 &&
                   protocol::checkString(data, "username");
        }

        bson::Document entityUpdate(const std::string &token, int64_t entity_id, const bson::Document &components) {
            bson::Document document;
            bson::Document message;

            message << u8"token" << token;
            message << u8"entity_id" << entity_id;
            message << u8"components" << components;

            document << u8"header" << protocol::createHeader("EntityUpdate");
            document << u8"data" << message;

            return document;
        }

        bool checkEntityUpdate(const bson::Document &document) {
            if (!protocol::checkMessage(document) ||
                document[u8"header"][u8"action"].getValueString() != u8"EntityUpdate")
                return false;
            bson::Document data = document[u8"data"].getValueDocument();
            return data.elementsCount() == 3 &&
                   protocol::checkString(data, u8"token") &&
                   data.hasKey(u8"entity_id") && data[u8"entity_id"].getValueType() == bson::INT64 &&
                   data.hasKey(u8"components") && data[u8"components"].getValueType() == bson::DOCUMENT;
        }

    }
}