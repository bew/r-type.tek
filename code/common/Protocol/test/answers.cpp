//
// Created by paccar_c on 12/14/16.
//

#include <gtest/gtest.h>
#include <stdlib.h>
#include "Answers.hh"

TEST(Answers, Ok) {
    std::string id("aComputer01");
    std::srand(std::time(0));
    int64_t timestamp = std::rand();
    bson::Document dataAnswer;
    dataAnswer << u8"login" << id;

    bson::Document answerOk = protocol::answers::ok(id, timestamp, dataAnswer);

    bson::Document header = answerOk["header"].getValueDocument();
    EXPECT_EQ(header["id"].getValueString(), id);
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

TEST(Answers, BadRequest) {
    std::string id("aComputer01");
    std::srand(std::time(0));
    int64_t timestamp = std::rand();

    bson::Document answerBadRequest = protocol::answers::badRequest(id, timestamp);

    bson::Document header = answerBadRequest["header"].getValueDocument();
    EXPECT_EQ(header["id"].getValueString(), id);
    EXPECT_EQ(header["magic"].getValueInt32(), MAGIC);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "Answer");
    EXPECT_EQ(header["version"].getValueString(), VERSION);


    bson::Document data = answerBadRequest["data"].getValueDocument();
    EXPECT_EQ(data["code"].getValueInt32(), 400);
    EXPECT_EQ(data["timestamp"].getValueInt64(), timestamp);
    EXPECT_EQ(data["message"].getValueString(), "Bad Request");
}

TEST(Answers, Unauthorized) {
    std::string id("aComputer01");
    std::srand(std::time(0));
    int64_t timestamp = std::rand();

    bson::Document answerUnauthorized = protocol::answers::unauthorized(id, timestamp);

    bson::Document header = answerUnauthorized["header"].getValueDocument();
    EXPECT_EQ(header["id"].getValueString(), id);
    EXPECT_EQ(header["magic"].getValueInt32(), MAGIC);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "Answer");
    EXPECT_EQ(header["version"].getValueString(), VERSION);


    bson::Document data = answerUnauthorized["data"].getValueDocument();
    EXPECT_EQ(data["code"].getValueInt32(), 401);
    EXPECT_EQ(data["timestamp"].getValueInt64(), timestamp);
    EXPECT_EQ(data["message"].getValueString(), "Unauthorized");
}

TEST(Answers, Forbidden) {
    std::string id("aComputer01");
    std::srand(std::time(0));
    int64_t timestamp = std::rand();

    bson::Document answerForbidden = protocol::answers::forbidden(id, timestamp);

    bson::Document header = answerForbidden["header"].getValueDocument();
    EXPECT_EQ(header["id"].getValueString(), id);
    EXPECT_EQ(header["magic"].getValueInt32(), MAGIC);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "Answer");
    EXPECT_EQ(header["version"].getValueString(), VERSION);


    bson::Document data = answerForbidden["data"].getValueDocument();
    EXPECT_EQ(data["code"].getValueInt32(), 403);
    EXPECT_EQ(data["timestamp"].getValueInt64(), timestamp);
    EXPECT_EQ(data["message"].getValueString(), "Forbidden");
}

TEST(Answers, NotFound) {
    std::string id("aComputer01");
    std::srand(std::time(0));
    int64_t timestamp = std::rand();

    bson::Document answerNotFound = protocol::answers::notFound(id, timestamp);

    bson::Document header = answerNotFound["header"].getValueDocument();
    EXPECT_EQ(header["id"].getValueString(), id);
    EXPECT_EQ(header["magic"].getValueInt32(), MAGIC);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "Answer");
    EXPECT_EQ(header["version"].getValueString(), VERSION);


    bson::Document data = answerNotFound["data"].getValueDocument();
    EXPECT_EQ(data["code"].getValueInt32(), 404);
    EXPECT_EQ(data["timestamp"].getValueInt64(), timestamp);
    EXPECT_EQ(data["message"].getValueString(), "Not Found");
}

TEST(Answers, TooManyRequests) {
    std::string id("aComputer01");
    std::srand(std::time(0));
    int64_t timestamp = std::rand();

    bson::Document answerTooManyRequests = protocol::answers::tooManyRequests(id, timestamp);

    bson::Document header = answerTooManyRequests["header"].getValueDocument();
    EXPECT_EQ(header["id"].getValueString(), id);
    EXPECT_EQ(header["magic"].getValueInt32(), MAGIC);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "Answer");
    EXPECT_EQ(header["version"].getValueString(), VERSION);


    bson::Document data = answerTooManyRequests["data"].getValueDocument();
    EXPECT_EQ(data["code"].getValueInt32(), 429);
    EXPECT_EQ(data["timestamp"].getValueInt64(), timestamp);
    EXPECT_EQ(data["message"].getValueString(), "Too Many Requests");
}

TEST(Answers, InternalServerError) {
    std::string id("aComputer01");
    std::srand(std::time(0));
    int64_t timestamp = std::rand();

    bson::Document answerInternalServerError = protocol::answers::internalServerError(id, timestamp);

    bson::Document header = answerInternalServerError["header"].getValueDocument();
    EXPECT_EQ(header["id"].getValueString(), id);
    EXPECT_EQ(header["magic"].getValueInt32(), MAGIC);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "Answer");
    EXPECT_EQ(header["version"].getValueString(), VERSION);


    bson::Document data = answerInternalServerError["data"].getValueDocument();
    EXPECT_EQ(data["code"].getValueInt32(), 500);
    EXPECT_EQ(data["timestamp"].getValueInt64(), timestamp);
    EXPECT_EQ(data["message"].getValueString(), "Internal Server Error");
}

TEST(Answers, NotImplemented) {
    std::string id("aComputer01");
    std::srand(std::time(0));
    int64_t timestamp = std::rand();

    bson::Document answerNotImplemented = protocol::answers::notImplemented(id, timestamp);

    bson::Document header = answerNotImplemented["header"].getValueDocument();
    EXPECT_EQ(header["id"].getValueString(), id);
    EXPECT_EQ(header["magic"].getValueInt32(), MAGIC);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "Answer");
    EXPECT_EQ(header["version"].getValueString(), VERSION);


    bson::Document data = answerNotImplemented["data"].getValueDocument();
    EXPECT_EQ(data["code"].getValueInt32(), 501);
    EXPECT_EQ(data["timestamp"].getValueInt64(), timestamp);
    EXPECT_EQ(data["message"].getValueString(), "Not Implemented");
}

TEST(Answers, ServiceUnavailable) {
    std::string id("aComputer01");
    std::srand(std::time(0));
    int64_t timestamp = std::rand();

    bson::Document answerServiceUnavailable = protocol::answers::serviceUnavailable(id, timestamp);

    bson::Document header = answerServiceUnavailable["header"].getValueDocument();
    EXPECT_EQ(header["id"].getValueString(), id);
    EXPECT_EQ(header["magic"].getValueInt32(), MAGIC);
    EXPECT_EQ(header["timestamp"].getValueType(), bson::INT64);
    EXPECT_EQ(header["action"].getValueString(), "Answer");
    EXPECT_EQ(header["version"].getValueString(), VERSION);


    bson::Document data = answerServiceUnavailable["data"].getValueDocument();
    EXPECT_EQ(data["code"].getValueInt32(), 503);
    EXPECT_EQ(data["timestamp"].getValueInt64(), timestamp);
    EXPECT_EQ(data["message"].getValueString(), "Service Unavailable");
}