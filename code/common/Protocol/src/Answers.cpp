/**
 * @file Answers.cpp
 * @brief serialize messages answers into BSON for R-Type protocol
 * @author Christopher Paccard
 *
 * Functions to serialize messages answers into BSON for the R-Type protocol
 *
 */

#include "Answers.hh"

namespace protocol {
    namespace answers {
        bson::Document ok(const std::string& id, int64_t timestamp, const std::string& message, const bson::Document& data) {
            bson::Document document;
            bson::Document answer;

            answer << u8"code" << 200;
            answer << u8"message" << message;
            answer << u8"timestamp" << timestamp;
            answer << u8"data" << data;

            document << u8"header" << protocol::getHeader(id, "Answer");
            document << u8"data" << answer;

            return document;
        }

        bson::Document badRequest(const std::string& id, int64_t timestamp, const std::string& message) {
            bson::Document document;
            bson::Document answer;

            answer << u8"code" << 400;
            answer << u8"message" << message;
            answer << u8"timestamp" << timestamp;

            document << u8"header" << protocol::getHeader(id, "Answer");
            document << u8"data" << answer;

            return document;
        }

        bson::Document unauthorized(const std::string& id, int64_t timestamp, const std::string& message) {
            bson::Document document;
            bson::Document answer;

            answer << u8"code" << 401;
            answer << u8"message" << message;
            answer << u8"timestamp" << timestamp;

            document << u8"header" << protocol::getHeader(id, "Answer");
            document << u8"data" << answer;

            return document;
        }

        bson::Document forbidden(const std::string& id, int64_t timestamp, const std::string& message) {
            bson::Document document;
            bson::Document answer;

            answer << u8"code" << 403;
            answer << u8"message" << message;
            answer << u8"timestamp" << timestamp;

            document << u8"header" << protocol::getHeader(id, "Answer");
            document << u8"data" << answer;

            return document;
        }

        bson::Document notFound(const std::string& id, int64_t timestamp, const std::string& message) {
            bson::Document document;
            bson::Document answer;

            answer << u8"code" << 404;
            answer << u8"message" << message;
            answer << u8"timestamp" << timestamp;

            document << u8"header" << protocol::getHeader(id, "Answer");
            document << u8"data" << answer;

            return document;
        }

        bson::Document toManyRequests(const std::string& id, int64_t timestamp, const std::string& message) {
            bson::Document document;
            bson::Document answer;

            answer << u8"code" << 429;
            answer << u8"message" << message;
            answer << u8"timestamp" << timestamp;

            document << u8"header" << protocol::getHeader(id, "Answer");
            document << u8"data" << answer;

            return document;
        }

        bson::Document internalServerError(const std::string& id, int64_t timestamp, const std::string& message) {
            bson::Document document;
            bson::Document answer;

            answer << u8"code" << 500;
            answer << u8"message" << message;
            answer << u8"timestamp" << timestamp;

            document << u8"header" << protocol::getHeader(id, "Answer");
            document << u8"data" << answer;

            return document;
        }

        bson::Document notImplemented(const std::string& id, int64_t timestamp, const std::string& message) {
            bson::Document document;
            bson::Document answer;

            answer << u8"code" << 501;
            answer << u8"message" << message;
            answer << u8"timestamp" << timestamp;

            document << u8"header" << protocol::getHeader(id, "Answer");
            document << u8"data" << answer;

            return document;
        }

        bson::Document serviceUnavailable(const std::string& id, int64_t timestamp, const std::string& message) {
            bson::Document document;
            bson::Document answer;

            answer << u8"code" << 503;
            answer << u8"message" << message;
            answer << u8"timestamp" << timestamp;

            document << u8"header" << protocol::getHeader(id, "Answer");
            document << u8"data" << answer;

            return document;
        }
    }
}