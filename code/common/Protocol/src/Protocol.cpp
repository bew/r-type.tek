/**
 * @file Protocol.cpp
 * @brief serialize messages into BSON for R-Type protocol
 * @author Christopher Paccard
 *
 * Functions to serialize messages into BSON for the R-Type protocol
 *
 */

#include <chrono>
#include "Protocol.hh"

namespace protocol {
    bson::Document createHeader(const std::string &action) {
        bson::Document header;

        header << u8"magic" << protocol::magic;
        header << u8"timestamp" << std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        header << u8"action" << action;
        header << u8"version" << std::string(protocol::version);

        return header;
    }

    typedef bool (*checkFunction)(const bson::Document&);
    static const std::map<std::string, checkFunction>checkFunctions = {
            {"Answer", &protocol::answers::checkAnswer},
    };

    bool checkHeader(const bson::Document& header) {
            return header.elementsCount() == 4 &&
                   header.hasKey(u8"magic") && header[u8"magic"].getValueType() == bson::INT32 && header[u8"magic"].getValueInt32() == protocol::magic &&
                   header.hasKey(u8"timestamp") && header[u8"timestamp"].getValueType() == bson::INT64 && header[u8"timestamp"].getValueInt64() > 0 &&
                   header.hasKey(u8"action") && header[u8"action"].getValueType() == bson::STRING && checkFunctions.count(header[u8"action"].getValueString()) &&
                   header.hasKey(u8"version") && header[u8"version"].getValueType() == bson::STRING && header[u8"version"].getValueString() == protocol::version;
    }

    bool checkMessage(const bson::Document& message) {
            return message.hasKey(u8"header") && protocol::checkHeader(message[u8"header"].getValueDocument()) &&
                   message.hasKey(u8"data") && message[u8"data"].getValueType() == bson::DOCUMENT &&
                   (*checkFunctions.at(message[u8"header"]["action"].getValueString()))(message[u8"data"]);
    }
}