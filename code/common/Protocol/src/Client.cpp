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
            return document.elementsCount() == 2 &&
                   protocol::checkString(document, u8"username") &&
                   protocol::checkString(document, u8"password");
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
            return document.elementsCount() == 2 &&
                   protocol::checkString(document, u8"username") &&
                   protocol::checkString(document, u8"password");
        }

        bson::Document logout(void) {
            bson::Document document;
            bson::Document message;

            document << u8"header" << protocol::createHeader("Logout");
            document << u8"data" << message;

            return document;
        }

        bool checkLogout(const bson::Document &document) {
            return !document.elementsCount();
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
            if (document.hasKey("password"))
                return document.elementsCount() == 2 &&
                       protocol::checkString(document, "name") &&
                       protocol::checkString(document, "password");
            else
                return document.elementsCount() == 2 &&
                       protocol::checkString(document, "name");
        }

        bson::Document roomLeave(void) {
            bson::Document document;
            bson::Document message;

            document << u8"header" << protocol::createHeader("RoomLeave");
            document << u8"data" << message;

            return document;
        }

        bool checkRoomLeave(const bson::Document &document) {
            return !document.elementsCount();
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

        bson::Document gameLeave(void) {
            bson::Document document;
            bson::Document message;

            document << u8"header" << protocol::createHeader("GameLeave");
            document << u8"data" << message;

            return document;
        }

        bool checkGameLeave(const bson::Document &document) {
            return !document.elementsCount();
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