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
        bson::Document signUp(const std::string &username, const std::string &password) {
            bson::Document document;
            bson::Document message;

            message << u8"username" << username;
            message << u8"password" << password;

            document << u8"header" << protocol::createHeader("SignUp");
            document << u8"data" << message;

            return document;
        }

        bool checkSignUp(const bson::Document &document) {
            if (!protocol::checkMessage(document) ||
                !protocol::checkHeader(document[u8"header"].getValueDocument()) ||
                document[u8"header"]["action"].getValueString() != u8"SignUp")
                return false;
            bson::Document data = document[u8"data"].getValueDocument();
            return data.elementsCount() == 2 &&
                   protocol::checkString(data, u8"username") &&
                   protocol::checkString(data, u8"password");
        }

        bson::Document login(const std::string &username, const std::string &password) {
            bson::Document document;
            bson::Document message;

            message << u8"username" << username;
            message << u8"password" << password;

            document << u8"header" << protocol::createHeader("Login");
            document << u8"data" << message;

            return document;
        }

        bool checkLogin(const bson::Document &document) {
            if (!protocol::checkMessage(document) ||
                !protocol::checkHeader(document[u8"header"].getValueDocument()) ||
                document[u8"header"]["action"].getValueString() != u8"Login")
                return false;
            bson::Document data = document[u8"data"].getValueDocument();
            return data.elementsCount() == 2 &&
                   protocol::checkString(data, u8"username") &&
                   protocol::checkString(data, u8"password");
        }

        bson::Document logout(void) {
            bson::Document document;
            bson::Document message;

            document << u8"header" << protocol::createHeader("Logout");
            document << u8"data" << message;

            return document;
        }

        bool checkLogout(const bson::Document &document) {
            if (!protocol::checkMessage(document) ||
                !protocol::checkHeader(document[u8"header"].getValueDocument()) ||
                document[u8"header"]["action"].getValueString() != u8"Logout")
                return false;
            bson::Document data = document[u8"data"].getValueDocument();
            return data.isEmpty();
        }

        bson::Document roomJoin(const std::string &name, const std::string &password) {
            bson::Document document;
            bson::Document message;

            message << u8"name" << name;
            if (!password.empty())
                message << u8"password" << password;

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
            if (data.hasKey("password"))
                return data.elementsCount() == 2 &&
                       protocol::checkString(data, "name") &&
                       protocol::checkString(data, "password");
            else
                return data.elementsCount() == 1 &&
                       protocol::checkString(data, "name");
        }

        bson::Document roomLeave(void) {
            bson::Document document;
            bson::Document message;

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
            return data.isEmpty();
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

        bson::Document gameLeave(void) {
            bson::Document document;
            bson::Document message;

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
            return data.isEmpty();
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

        bool checkEntityUpdate(const bson::Document &document) {
            if (!protocol::checkMessage(document) ||
                !protocol::checkHeader(document[u8"header"].getValueDocument()) ||
                document[u8"header"]["action"].getValueString() != u8"EntityUpdate")
                return false;
            bson::Document data = document[u8"data"].getValueDocument();
            return data.elementsCount() == 2 &&
                   data.hasKey(u8"entity_id") && data[u8"entity_id"].getValueType() == bson::INT64 &&
                   data.hasKey(u8"components") && data[u8"components"].getValueType() == bson::DOCUMENT;
        }

    }
}