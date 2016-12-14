/**
 * @file answers.cpp
 * @brief answers test file
 * @author Christopher Paccard
 *
 * Contain all the the test to check answers
 *
 */

#include <gtest/gtest.h>
#include <stdlib.h>
#include "Answers.hh"

/**
 * Check answer ok (200)
 */
TEST(Answers, Ok) {
    std::srand(std::time(0));
    int64_t timestamp = std::rand();
    bson::Document dataAnswer;
    dataAnswer << u8"login" << std::string("toto42sh");

    bson::Document answerOk = protocol::answers::ok(timestamp, dataAnswer);

    bson::Document header = answerOk["header"].getValueDocument();
    EXPECT_EQ(header["magic"].getValueInt32(), MAGIC);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "Answer");
    EXPECT_EQ(header["version"].getValueString(), VERSION);


    bson::Document data = answerOk["data"].getValueDocument();
    EXPECT_EQ(data["code"].getValueInt32(), 200);
    EXPECT_EQ(data["timestamp"].getValueInt64(), timestamp);
    EXPECT_EQ(data["message"].getValueString(), "Ok");
    EXPECT_EQ(data["data"].getValueDocument(), dataAnswer);
}

/**
 * Check answer bad request (400)
 */
TEST(Answers, BadRequest) {
    std::srand(std::time(0));
    int64_t timestamp = std::rand();

    bson::Document answerBadRequest = protocol::answers::badRequest(timestamp);

    bson::Document header = answerBadRequest["header"].getValueDocument();
    EXPECT_EQ(header["magic"].getValueInt32(), MAGIC);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "Answer");
    EXPECT_EQ(header["version"].getValueString(), VERSION);


    bson::Document data = answerBadRequest["data"].getValueDocument();
    EXPECT_EQ(data["code"].getValueInt32(), 400);
    EXPECT_EQ(data["timestamp"].getValueInt64(), timestamp);
    EXPECT_EQ(data["message"].getValueString(), "Bad Request");
}

/**
 * Check answer unauthorized (401)
 */
TEST(Answers, Unauthorized) {
    std::srand(std::time(0));
    int64_t timestamp = std::rand();

    bson::Document answerUnauthorized = protocol::answers::unauthorized(timestamp);

    bson::Document header = answerUnauthorized["header"].getValueDocument();
    EXPECT_EQ(header["magic"].getValueInt32(), MAGIC);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "Answer");
    EXPECT_EQ(header["version"].getValueString(), VERSION);


    bson::Document data = answerUnauthorized["data"].getValueDocument();
    EXPECT_EQ(data["code"].getValueInt32(), 401);
    EXPECT_EQ(data["timestamp"].getValueInt64(), timestamp);
    EXPECT_EQ(data["message"].getValueString(), "Unauthorized");
}

/**
 * Check answer forbidden (403)
 */
TEST(Answers, Forbidden) {
    std::srand(std::time(0));
    int64_t timestamp = std::rand();

    bson::Document answerForbidden = protocol::answers::forbidden(timestamp);

    bson::Document header = answerForbidden["header"].getValueDocument();
    EXPECT_EQ(header["magic"].getValueInt32(), MAGIC);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "Answer");
    EXPECT_EQ(header["version"].getValueString(), VERSION);


    bson::Document data = answerForbidden["data"].getValueDocument();
    EXPECT_EQ(data["code"].getValueInt32(), 403);
    EXPECT_EQ(data["timestamp"].getValueInt64(), timestamp);
    EXPECT_EQ(data["message"].getValueString(), "Forbidden");
}

/**
 * Check answer not found (404)
 */
TEST(Answers, NotFound) {
    std::srand(std::time(0));
    int64_t timestamp = std::rand();

    bson::Document answerNotFound = protocol::answers::notFound(timestamp);

    bson::Document header = answerNotFound["header"].getValueDocument();
    EXPECT_EQ(header["magic"].getValueInt32(), MAGIC);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "Answer");
    EXPECT_EQ(header["version"].getValueString(), VERSION);


    bson::Document data = answerNotFound["data"].getValueDocument();
    EXPECT_EQ(data["code"].getValueInt32(), 404);
    EXPECT_EQ(data["timestamp"].getValueInt64(), timestamp);
    EXPECT_EQ(data["message"].getValueString(), "Not Found");
}

/**
 * Check answer too many requests (429)
 */
TEST(Answers, TooManyRequests) {
    std::srand(std::time(0));
    int64_t timestamp = std::rand();

    bson::Document answerTooManyRequests = protocol::answers::tooManyRequests(timestamp);

    bson::Document header = answerTooManyRequests["header"].getValueDocument();
    EXPECT_EQ(header["magic"].getValueInt32(), MAGIC);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "Answer");
    EXPECT_EQ(header["version"].getValueString(), VERSION);


    bson::Document data = answerTooManyRequests["data"].getValueDocument();
    EXPECT_EQ(data["code"].getValueInt32(), 429);
    EXPECT_EQ(data["timestamp"].getValueInt64(), timestamp);
    EXPECT_EQ(data["message"].getValueString(), "Too Many Requests");
}

/**
 * Check answer internal server error (500)
 */
TEST(Answers, InternalServerError) {
    std::srand(std::time(0));
    int64_t timestamp = std::rand();

    bson::Document answerInternalServerError = protocol::answers::internalServerError(timestamp);

    bson::Document header = answerInternalServerError["header"].getValueDocument();
    EXPECT_EQ(header["magic"].getValueInt32(), MAGIC);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "Answer");
    EXPECT_EQ(header["version"].getValueString(), VERSION);


    bson::Document data = answerInternalServerError["data"].getValueDocument();
    EXPECT_EQ(data["code"].getValueInt32(), 500);
    EXPECT_EQ(data["timestamp"].getValueInt64(), timestamp);
    EXPECT_EQ(data["message"].getValueString(), "Internal Server Error");
}

/**
 * Check answer not implemented (501)
 */
TEST(Answers, NotImplemented) {
    std::srand(std::time(0));
    int64_t timestamp = std::rand();

    bson::Document answerNotImplemented = protocol::answers::notImplemented(timestamp);

    bson::Document header = answerNotImplemented["header"].getValueDocument();
    EXPECT_EQ(header["magic"].getValueInt32(), MAGIC);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "Answer");
    EXPECT_EQ(header["version"].getValueString(), VERSION);


    bson::Document data = answerNotImplemented["data"].getValueDocument();
    EXPECT_EQ(data["code"].getValueInt32(), 501);
    EXPECT_EQ(data["timestamp"].getValueInt64(), timestamp);
    EXPECT_EQ(data["message"].getValueString(), "Not Implemented");
}

/**
 * Check answer service unavailable (503)
 */
TEST(Answers, ServiceUnavailable) {
    std::srand(std::time(0));
    int64_t timestamp = std::rand();

    bson::Document answerServiceUnavailable = protocol::answers::serviceUnavailable(timestamp);

    bson::Document header = answerServiceUnavailable["header"].getValueDocument();
    EXPECT_EQ(header["magic"].getValueInt32(), MAGIC);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "Answer");
    EXPECT_EQ(header["version"].getValueString(), VERSION);


    bson::Document data = answerServiceUnavailable["data"].getValueDocument();
    EXPECT_EQ(data["code"].getValueInt32(), 503);
    EXPECT_EQ(data["timestamp"].getValueInt64(), timestamp);
    EXPECT_EQ(data["message"].getValueString(), "Service Unavailable");
}