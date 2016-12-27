/**
 * @file answers.cpp
 * @brief answers test file
 * @author Christopher Paccard
 *
 * Contain all the the test to check answers
 *
 */

#include <gtest/gtest.h>
#include <chrono>
#include "Answers.hh"

/**
 * Check answer ok (200)
 */
TEST(Answers, Ok) {
    int64_t timestamp = std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    bson::Document dataAnswer;
    dataAnswer << u8"login" << std::string("toto42sh");

    bson::Document answerOk = protocol::answers::ok(timestamp, dataAnswer);

    bson::Document header = answerOk["header"].getValueDocument();
    EXPECT_EQ(header["magic"].getValueInt32(), protocol::magic);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "Answer");
    EXPECT_EQ(header["version"].getValueString(), protocol::version);


    bson::Document data = answerOk["data"].getValueDocument();
    EXPECT_EQ(data["code"].getValueInt32(), 200);
    EXPECT_EQ(data["timestamp"].getValueInt64(), timestamp);
    EXPECT_EQ(data["message"].getValueString(), "Ok");
    EXPECT_EQ(data["data"].getValueDocument(), dataAnswer);

    EXPECT_EQ(protocol::answers::checkAnswer(answerOk), true);
}

/**
 * Check answer bad request (400)
 */
TEST(Answers, BadRequest) {
    int64_t timestamp = std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()).count();

    bson::Document answerBadRequest = protocol::answers::badRequest(timestamp);

    bson::Document header = answerBadRequest["header"].getValueDocument();
    EXPECT_EQ(header["magic"].getValueInt32(), protocol::magic);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "Answer");
    EXPECT_EQ(header["version"].getValueString(), protocol::version);


    bson::Document data = answerBadRequest["data"].getValueDocument();
    EXPECT_EQ(data["code"].getValueInt32(), 400);
    EXPECT_EQ(data["timestamp"].getValueInt64(), timestamp);
    EXPECT_EQ(data["message"].getValueString(), "Bad Request");

    EXPECT_EQ(protocol::answers::checkAnswer(answerBadRequest), true);
}

/**
 * Check answer unauthorized (401)
 */
TEST(Answers, Unauthorized) {
    int64_t timestamp = std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()).count();

    bson::Document answerUnauthorized = protocol::answers::unauthorized(timestamp);

    bson::Document header = answerUnauthorized["header"].getValueDocument();
    EXPECT_EQ(header["magic"].getValueInt32(), protocol::magic);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "Answer");
    EXPECT_EQ(header["version"].getValueString(), protocol::version);


    bson::Document data = answerUnauthorized["data"].getValueDocument();
    EXPECT_EQ(data["code"].getValueInt32(), 401);
    EXPECT_EQ(data["timestamp"].getValueInt64(), timestamp);
    EXPECT_EQ(data["message"].getValueString(), "Unauthorized");

    EXPECT_EQ(protocol::answers::checkAnswer(answerUnauthorized), true);
}

/**
 * Check answer forbidden (403)
 */
TEST(Answers, Forbidden) {
    int64_t timestamp = std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()).count();

    bson::Document answerForbidden = protocol::answers::forbidden(timestamp);

    bson::Document header = answerForbidden["header"].getValueDocument();
    EXPECT_EQ(header["magic"].getValueInt32(), protocol::magic);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "Answer");
    EXPECT_EQ(header["version"].getValueString(), protocol::version);


    bson::Document data = answerForbidden["data"].getValueDocument();
    EXPECT_EQ(data["code"].getValueInt32(), 403);
    EXPECT_EQ(data["timestamp"].getValueInt64(), timestamp);
    EXPECT_EQ(data["message"].getValueString(), "Forbidden");


    EXPECT_EQ(protocol::answers::checkAnswer(answerForbidden), true);
}

/**
 * Check answer not found (404)
 */
TEST(Answers, NotFound) {
    int64_t timestamp = std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()).count();

    bson::Document answerNotFound = protocol::answers::notFound(timestamp);

    bson::Document header = answerNotFound["header"].getValueDocument();
    EXPECT_EQ(header["magic"].getValueInt32(), protocol::magic);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "Answer");
    EXPECT_EQ(header["version"].getValueString(), protocol::version);


    bson::Document data = answerNotFound["data"].getValueDocument();
    EXPECT_EQ(data["code"].getValueInt32(), 404);
    EXPECT_EQ(data["timestamp"].getValueInt64(), timestamp);
    EXPECT_EQ(data["message"].getValueString(), "Not Found");


    EXPECT_EQ(protocol::answers::checkAnswer(answerNotFound), true);
}

/**
 * Check answer too many requests (429)
 */
TEST(Answers, TooManyRequests) {
    int64_t timestamp = std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()).count();

    bson::Document answerTooManyRequests = protocol::answers::tooManyRequests(timestamp);

    bson::Document header = answerTooManyRequests["header"].getValueDocument();
    EXPECT_EQ(header["magic"].getValueInt32(), protocol::magic);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "Answer");
    EXPECT_EQ(header["version"].getValueString(), protocol::version);


    bson::Document data = answerTooManyRequests["data"].getValueDocument();
    EXPECT_EQ(data["code"].getValueInt32(), 429);
    EXPECT_EQ(data["timestamp"].getValueInt64(), timestamp);
    EXPECT_EQ(data["message"].getValueString(), "Too Many Requests");

    EXPECT_EQ(protocol::answers::checkAnswer(answerTooManyRequests), true);
}

/**
 * Check answer internal server error (500)
 */
TEST(Answers, InternalServerError) {
    int64_t timestamp = std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()).count();

    bson::Document answerInternalServerError = protocol::answers::internalServerError(timestamp);

    bson::Document header = answerInternalServerError["header"].getValueDocument();
    EXPECT_EQ(header["magic"].getValueInt32(), protocol::magic);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "Answer");
    EXPECT_EQ(header["version"].getValueString(), protocol::version);


    bson::Document data = answerInternalServerError["data"].getValueDocument();
    EXPECT_EQ(data["code"].getValueInt32(), 500);
    EXPECT_EQ(data["timestamp"].getValueInt64(), timestamp);
    EXPECT_EQ(data["message"].getValueString(), "Internal Server Error");

    EXPECT_EQ(protocol::answers::checkAnswer(answerInternalServerError), true);
}

/**
 * Check answer not implemented (501)
 */
TEST(Answers, NotImplemented) {
    int64_t timestamp = std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()).count();

    bson::Document answerNotImplemented = protocol::answers::notImplemented(timestamp);

    bson::Document header = answerNotImplemented["header"].getValueDocument();
    EXPECT_EQ(header["magic"].getValueInt32(), protocol::magic);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "Answer");
    EXPECT_EQ(header["version"].getValueString(), protocol::version);


    bson::Document data = answerNotImplemented["data"].getValueDocument();
    EXPECT_EQ(data["code"].getValueInt32(), 501);
    EXPECT_EQ(data["timestamp"].getValueInt64(), timestamp);
    EXPECT_EQ(data["message"].getValueString(), "Not Implemented");

    EXPECT_EQ(protocol::answers::checkAnswer(answerNotImplemented), true);
}

/**
 * Check answer service unavailable (503)
 */
TEST(Answers, ServiceUnavailable) {
    int64_t timestamp = std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()).count();

    bson::Document answerServiceUnavailable = protocol::answers::serviceUnavailable(timestamp);

    bson::Document header = answerServiceUnavailable["header"].getValueDocument();
    EXPECT_EQ(header["magic"].getValueInt32(), protocol::magic);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "Answer");
    EXPECT_EQ(header["version"].getValueString(), protocol::version);


    bson::Document data = answerServiceUnavailable["data"].getValueDocument();
    EXPECT_EQ(data["code"].getValueInt32(), 503);
    EXPECT_EQ(data["timestamp"].getValueInt64(), timestamp);
    EXPECT_EQ(data["message"].getValueString(), "Service Unavailable");

    EXPECT_EQ(protocol::answers::checkAnswer(answerServiceUnavailable), true);
}