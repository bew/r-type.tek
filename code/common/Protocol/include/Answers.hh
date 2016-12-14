/**
 * @file Answers.hh
 * @brief serialize messages answers into BSON for R-Type protocol
 * @author Christopher Paccard
 *
 * Functions to serialize messages answers into BSON for the R-Type protocol
 *
 */

#ifndef PROTOCOL_ANSWERS_HH
#define PROTOCOL_ANSWERS_HH

#include "Protocol.hh"

namespace protocol {
    namespace answers {
        /**
         * Mean that the request has been correctly handle and everything went right (200)
         *
         * @param id the id of whom send the message
         * @param timestamp the timestamp of the answered command
         * @param message a message which will be included into the answer
         * @param data a bson Document which will be included into the answer
         * @return the bson Document formatted for the following answer
         */
        bson::Document ok(const std::string& id, int64_t timestamp, const bson::Document& data = bson::Document(), const std::string& message = "Ok");

        /**
         * Mean that the request which has been received is a bad request (malformed request syntax)
         * The request will be ignored (400)
         *
         * @param id the id of whom send the message
         * @param timestamp the timestamp of the answered command
         * @param message a message which will be included into the answer
         * @return the bson Document formatted for the following answer
         */
        bson::Document badRequest(const std::string& id, int64_t timestamp, const std::string& message = "Bad Request");

        /**
         * Mean that the request is unauthorized, specifically for use when authentication is
         * required and has failed or has not yet been provided (401)
         *
         * @param id the id of whom send the message
         * @param timestamp the timestamp of the answered command
         * @param message a message which will be included into the answer
         * @return the bson Document formatted for the following answer
         */
        bson::Document unauthorized(const std::string& id, int64_t timestamp, const std::string& message = "Unauthorized");

        /**
         * Mean that the request was a valid request, but the server is refusing to respond to it
         * The user might be logged in but does not have the necessary permissions for the resource (403)
         *
         * @param id the id of whom send the message
         * @param timestamp the timestamp of the answered command
         * @param message a message which will be included into the answer
         * @return the bson Document formatted for the following answer
         */
        bson::Document forbidden(const std::string& id, int64_t timestamp, const std::string& message = "Forbidden");

        /**
         * Mean that the request has been ignored because the requested resource could not be found (404)
         *
         * @param id the id of whom send the message
         * @param timestamp the timestamp of the answered command
         * @param message a message which will be included into the answer
         * @return the bson Document formatted for the following answer
         */
        bson::Document notFound(const std::string& id, int64_t timestamp, const std::string& message = "Not Found");

        /**
         * Mean that the request has been ignored because the user has sent too many requests
         * in a given amount of time (429)
         *
         * @param id the id of whom send the message
         * @param timestamp the timestamp of the answered command
         * @param message a message which will be included into the answer
         * @return the bson Document formatted for the following answer
         */
        bson::Document tooManyRequests(const std::string& id, int64_t timestamp, const std::string& message = "Too Many Requests");

        /**
         * Mean that the request has generate an internal error but without more precisions of the error's nature (500)
         *
         * @param timestamp the timestamp of the answered command
         * @param message a message which will be included into the answer
         * @return the bson Document formatted for the following answer
         */
        bson::Document internalServerError(const std::string& id, int64_t timestamp, const std::string& message = "Internal Server Error");

        /**
         * Mean that the request action is either not recognize or the version are not compatible for the receiver (501)
         *
         * @param id the id of whom send the message
         * @param timestamp the timestamp of the answered command
         * @param message a message which will be included into the answer
         * @return the bson Document formatted for the following answer
         */
        bson::Document notImplemented(const std::string& id, int64_t timestamp, const std::string& message = "Not Implemented");

        /**
         * mean that the request has been ignored because the receiver is currently unavailable
         * (because it is overloaded or down for maintenance). Generally, this is a temporary state (503)
         *
         * @param id the id of whom send the message
         * @param timestamp the timestamp of the answered command
         * @param message a message which will be included into the answer
         * @return the bson Document formatted for the following answer
         */
        bson::Document serviceUnavailable(const std::string& id, int64_t timestamp, const std::string& message = "Service Unavailable");
    }
}

#endif //PROJECT_ANSWERS_HH
