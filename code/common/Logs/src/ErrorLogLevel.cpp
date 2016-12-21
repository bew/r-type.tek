/**
 * @file ErrorLogLevel.cpp
 * @brief Error log level class
 * @author Christopher Paccard
 *
 * Error log level class for Logger
 *
 */

#include "ErrorLogLevel.hh"

namespace logs {
    ErrorLogLevel::ErrorLogLevel() {
        logger.registerLogLevel(this);
    }

    ErrorLogLevel::~ErrorLogLevel() {
    }

    std::string ErrorLogLevel::getLogLevelName() const {
        return logs::ERROR;
    }

    std::ostream &ErrorLogLevel::getLogLevelStream() const {
        return std::cerr;
    }

    static ErrorLogLevel errorLogLevel;
}