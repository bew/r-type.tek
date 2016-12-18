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
}