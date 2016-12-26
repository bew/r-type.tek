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
#include "Answers.hh"
#include "Server.hh"
#include "Client.hh"

/**
 * Contain all functions to use for the R-Type protocol
 */
namespace protocol {

    /**
     * Magic number of protocol
     */
    const int32_t magic = 1918729278;

    /**
     * Version of the protocol
     */
    const std::string version = "0.1";

    /**
     * Get a valid header Document for the R-Type protocol
     *
     * @param action the action that will be put into the header Document
     * @return the Document that represent a header for the R-Type protocol
     */
    bson::Document createHeader(const std::string &action);

    /**
     * Check if the given Document is a correct message header
     *
     * @param header the Document to check
     * @return true if the Document is correct, else false
     */
    bool checkHeader(const bson::Document& header);

    /**
     * Check if the given Document is a correct message (depending on the action)
     *
     * @param message the Document to check
     * @return true if the Document is correct, else false
     */
    bool checkMessage(const bson::Document& message);
}

#endif //PROTOCOL_PROTOCOL_HH
