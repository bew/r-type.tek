/**
 * @file InfoLogLevel.cpp
 * @brief Info log level class
 * @author Christopher Paccard
 *
 * Info log level class for Logger
 *
 */

#include "InfoLogLevel.hh"

namespace logs {
    InfoLogLevel::InfoLogLevel() {
        logger.registerLogLevel(this);
    }

    InfoLogLevel::~InfoLogLevel() {
    }

    std::string InfoLogLevel::getLogLevelName() const {
        return logs::INFO;
    }

    std::ostream &InfoLogLevel::getLogLevelStream() {
        return std::cout;
    }

    static InfoLogLevel infoLogLevel;
}