/**
 * @file Answers.cpp
 * @brief serialize messages answers into BSON for R-Type protocol
 * @author Christopher Paccard
 *
 * Functions to serialize messages answers into BSON for the R-Type protocol
 *
 */

#include <set>
#include "Answers.hh"

namespace protocol {
    namespace answers {
        bson::Document ok(int64_t timestamp, const bson::Document &data, const std::string &message) {
            bson::Document document;
            bson::Document answer;

            answer << u8"code" << 200;
            answer << u8"message" << message;
            answer << u8"timestamp" << timestamp;
            answer << u8"data" << data;

            document << u8"header" << protocol::createHeader("Answer");
            document << u8"data" << answer;

            return document;
        }

        bson::Document badRequest(int64_t timestamp, const std::string &message) {
            bson::Document document;
            bson::Document answer;

            answer << u8"code" << 400;
            answer << u8"message" << message;
            answer << u8"timestamp" << timestamp;

            document << u8"header" << protocol::createHeader("Answer");
            document << u8"data" << answer;

            return document;
        }

        bson::Document unauthorized(int64_t timestamp, const std::string &message) {
            bson::Document document;
            bson::Document answer;

            answer << u8"code" << 401;
            answer << u8"message" << message;
            answer << u8"timestamp" << timestamp;

            document << u8"header" << protocol::createHeader("Answer");
            document << u8"data" << answer;

            return document;
        }

        bson::Document forbidden(int64_t timestamp, const std::string &message) {
            bson::Document document;
            bson::Document answer;

            answer << u8"code" << 403;
            answer << u8"message" << message;
            answer << u8"timestamp" << timestamp;

            document << u8"header" << protocol::createHeader("Answer");
            document << u8"data" << answer;

            return document;
        }

        bson::Document notFound(int64_t timestamp, const std::string &message) {
            bson::Document document;
            bson::Document answer;

            answer << u8"code" << 404;
            answer << u8"message" << message;
            answer << u8"timestamp" << timestamp;

            document << u8"header" << protocol::createHeader("Answer");
            document << u8"data" << answer;

            return document;
        }

        bson::Document tooManyRequests(int64_t timestamp, const std::string &message) {
            bson::Document document;
            bson::Document answer;

            answer << u8"code" << 429;
            answer << u8"message" << message;
            answer << u8"timestamp" << timestamp;

            document << u8"header" << protocol::createHeader("Answer");
            document << u8"data" << answer;

            return document;
        }

        bson::Document internalServerError(int64_t timestamp, const std::string &message) {
            bson::Document document;
            bson::Document answer;

            answer << u8"code" << 500;
            answer << u8"message" << message;
            answer << u8"timestamp" << timestamp;

            document << u8"header" << protocol::createHeader("Answer");
            document << u8"data" << answer;

            return document;
        }

        bson::Document notImplemented(int64_t timestamp, const std::string &message) {
            bson::Document document;
            bson::Document answer;

            answer << u8"code" << 501;
            answer << u8"message" << message;
            answer << u8"timestamp" << timestamp;

            document << u8"header" << protocol::createHeader("Answer");
            document << u8"data" << answer;

            return document;
        }

        bson::Document serviceUnavailable(int64_t timestamp, const std::string &message) {
            bson::Document document;
            bson::Document answer;

            answer << u8"code" << 503;
            answer << u8"message" << message;
            answer << u8"timestamp" << timestamp;

            document << u8"header" << protocol::createHeader("Answer");
            document << u8"data" << answer;

            return document;
        }

        bool checkCode(const bson::Document &document) {
            static const std::set<int32_t> codes = {200, 400, 401, 403, 404, 429, 500, 501, 503};

            if (document.hasKey(u8"code") && document[u8"code"].getValueType() == bson::INT32 &&
                codes.count(document[u8"code"].getValueInt32())) {
                if (document[u8"code"].getValueInt32() != 200 && document.elementsCount() == 2)
                    return true;
                else if (document[u8"code"].getValueInt32() == 200 && document.elementsCount() == 3 &&
                         document.hasKey(u8"data") && document[u8"data"].getValueType() == bson::DOCUMENT)
                    return true;
            }
            return false;
        }

        bool checkDocument(const bson::Document &document) {
            return protocol::answers::checkCode(document) &&
                   protocol::checkString(document, u8"message") &&
                   protocol::checkTimestamp(document);
        }
    }
}