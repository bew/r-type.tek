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
    DebugLogLevel::DebugLogLevel() {
        logger.registerLogLevel(this);
    }

    DebugLogLevel::~DebugLogLevel() {
    }

    std::string DebugLogLevel::getLogLevelName() const {
        return logs::DEBUG;
    }

    std::ostream &DebugLogLevel::getLogLevelStream() const {
        return std::cout;
    }

    static DebugLogLevel debugLogLevel;
}