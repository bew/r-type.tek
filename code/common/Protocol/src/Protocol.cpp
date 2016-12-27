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
        header << u8"timestamp" << std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        header << u8"action" << action;
        header << u8"version" << std::string(protocol::version);

        return header;
    }

    bool checkString(const bson::Document &document, const std::string &key) {
        return document.hasKey(key) &&
               document[key].getValueType() == bson::STRING &&
               !document[key].getValueString().empty();
    }

    bool checkMagic(const bson::Document &document) {
        return document.hasKey(u8"magic") &&
               document[u8"magic"].getValueType() == bson::INT32 &&
               document[u8"magic"].getValueInt32() == protocol::magic;
    }

    bool checkTimestamp(const bson::Document &document) {
        int64_t now = std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        return document.hasKey(u8"timestamp") &&
               document[u8"timestamp"].getValueType() == bson::INT64 &&
               document[u8"timestamp"].getValueInt64() >= (now - (protocol::latency + 86400)) &&
               document[u8"timestamp"].getValueInt64() <= (now + (protocol::latency + 86400)); // We never know
    }

    bool checkAction(const bson::Document &document) {
        return protocol::checkString(document, u8"action");
    }

    bool checkVersion(const bson::Document &document) {
        return document.hasKey(u8"version") &&
               document[u8"version"].getValueType() == bson::STRING &&
               document[u8"version"].getValueString() == protocol::version;
    }

    bool checkHeader(const bson::Document &document) {
        return document.elementsCount() == 4 &&
               protocol::checkMagic(document) &&
               protocol::checkTimestamp(document) &&
               protocol::checkAction(document) &&
               protocol::checkVersion(document);
    }

    bool checkMessage(const bson::Document &document) {
        return document.elementsCount() == 2 &&
               document.hasKey(u8"header") && document[u8"header"].getValueType() == bson::DOCUMENT &&
               protocol::checkHeader(document[u8"header"].getValueDocument()) &&
               document.hasKey(u8"data") && document[u8"data"].getValueType() == bson::DOCUMENT;
    }
}