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
    ErrorLogLevel::ErrorLogLevel() {}

    ErrorLogLevel::~ErrorLogLevel() {
    }

    std::string ErrorLogLevel::getLogLevelName() const {
        return logs::ERRORS;
    }

    std::ostream &ErrorLogLevel::getLogLevelStream() {
        return std::cerr;
    }

    ErrorLogLevel errorLogLevel;
}