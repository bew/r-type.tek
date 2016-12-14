/**
 * @file Protocol.hh
 * @brief serialize messages into BSON for R-Type protocol
 * @author Christopher Paccard
 *
 * Functions to serialize messages into BSON for the R-Type protocol
 *
 */

#include <chrono>
#include "Protocol.hh"

namespace protocol {
    bson::Document getHeader(const std::string& id, const std::string& action) {
        bson::Document header;

        header << "id" << id;
        header << "magic" << MAGIC;
        header << "timestamp" << std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        header << "action" << action;
        header << "version" << VERSION;

        return header;
    }
}