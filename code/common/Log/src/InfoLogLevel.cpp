/**
 * @file InfoLogLevel.cpp
 * @brief Info log level class
 * @author Christopher Paccard
 *
 * Info log level class for Logger
 *
 */

#include "InfoLogLevel.hh"

namespace log {
    InfoLogLevel::InfoLogLevel() {
        logger.registerLog(this);
    }

    InfoLogLevel::~InfoLogLevel() {
    }

    std::string InfoLogLevel::getLogLevelName() const {
        return log::INFO;
    }

    std::ostream &InfoLogLevel::getLogLevelStream() const {
        return std::cout;
    }

    InfoLogLevel infoLogLevel;
}