/**
 * @file DebugLogLevel.cpp
 * @brief Debug log level class
 * @author Christopher Paccard
 *
 * Debug log level class for Logger
 *
 */

#include "DebugLogLevel.hh"

namespace logs {
    DebugLogLevel::DebugLogLevel() {}

    DebugLogLevel::~DebugLogLevel() {
    }

    std::string DebugLogLevel::getLogLevelName() const {
        return logs::DEBUG;
    }

    std::ostream &DebugLogLevel::getLogLevelStream() {
        return std::cout;
    }

    DebugLogLevel debugLogLevel;
}