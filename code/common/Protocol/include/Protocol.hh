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
     * Allowed time in sec for a message to be interpreted (based on current and time +/- 1day).
     */
    const int64_t latency = 300;

    /**
     * Get a valid header Document for the R-Type protocol
     *
     * @param action the action that will be put into the header Document
     * @return the Document that represent a header for the R-Type protocol
     */
    bson::Document createHeader(const std::string &action);

    /**
     * Check if the key inside the Document exist, is a string and is not empty
     *
     * @param document the Document to check
     * @param key the key to check inside the Document
     * @return true if the Document is correct, else false
     */
    bool checkString(const bson::Document& document, const std::string& key);

    /**
     * Check if the magic is right inside the given Document
     *
     * @param document the Document to check
     * @return true if the magic is right, else false
     */
    bool checkMagic(const bson::Document &document);

    /**
     * Check if the timestamp is right inside the given Document
     *
     * @param document the Document to check
     * @return true if the timestamp is right, else false
     */
    bool checkTimestamp(const bson::Document &document);

    /**
     * Check if the action is right inside the given Document
     *
     * @param document the Document to check
     * @return true if the action is right, else false
     */
    bool checkAction(const bson::Document &document);

    /**
     * Check if the version is right inside the given Document
     *
     * @param document the Document to check
     * @return true if the version is right, else false
     */
    bool checkVersion(const bson::Document &document);

    /**
     * Check if the given Document is a correct header message
     *
     * @param document the Document to check
     * @return true if the Document is correct, else false
     */
    bool checkHeader(const bson::Document &document);

    /**
     * Check if the given Document is a correct message
     *
     * @param document the Document to check
     * @return true if the Document is correct, else false
     */
    bool checkMessage(const bson::Document &document);
}

#endif //PROTOCOL_PROTOCOL_HH
