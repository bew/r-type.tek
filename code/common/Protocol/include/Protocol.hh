/**
 * @file Protocol.hh
 * @brief serialize messages into BSON for R-Type protocol
 * @author Christopher Paccard
 *
 * Functions to serialize messages into BSON for the R-Type protocol
 *
 */

#ifndef PROTOCOL_PROTOCOL_HH
#define PROTOCOL_PROTOCOL_HH

#include "BSON/Document.hh"

#define MAGIC 1918729278
#define VERSION "0.1"

/**
 * Contain all functions to use for the R-Type protocol
 */
namespace protocol {
    /**
     * Get a valid header Document for the R-Type protocol
     *
     * @param id the id of who send the message
     * @param action the action that will be put into the header Document
     * @return the Document that represent a header for the R-Type protocol
     */
    bson::Document getHeader(const std::string &id, const std::string& action);
}

#endif //PROTOCOL_PROTOCOL_HH
