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
                !protocol::checkHeader(document[u8"header"].getValueDocument()) ||
                document[u8"header"]["action"].getValueString() != u8"RoomJoin")
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
                !protocol::checkHeader(document[u8"header"].getValueDocument()) ||
                document[u8"header"]["action"].getValueString() != u8"RoomLeave")
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
                !protocol::checkHeader(document[u8"header"].getValueDocument()) ||
                document[u8"header"]["action"].getValueString() != u8"RoomKick")
                return false;
            bson::Document data = document[u8"data"].getValueDocument();
            return data.elementsCount() == 1 &&
                   protocol::checkString(data, "username");
        }

        bson::Document gameStart(void) {
            bson::Document document;
            bson::Document message;

            document << u8"header" << protocol::createHeader("GameStart");
            document << u8"data" << message;

            return document;
        }

        bool checkGameStart(const bson::Document &document) {
            if (!protocol::checkMessage(document) ||
                !protocol::checkHeader(document[u8"header"].getValueDocument()) ||
                document[u8"header"]["action"].getValueString() != u8"GameStart")
                return false;
            bson::Document data = document[u8"data"].getValueDocument();
            return data.isEmpty();
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
                !protocol::checkHeader(document[u8"header"].getValueDocument()) ||
                document[u8"header"]["action"].getValueString() != u8"GameLeave")
                return false;
            bson::Document data = document[u8"data"].getValueDocument();
            return data.elementsCount() == 1 &&
                   protocol::checkString(data, "username");
        }

        bson::Document entityUpdate(int64_t entity_id, const bson::Document &components) {
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