/**
 * @file ServerLogLevel.cpp
 * @brief Server log level class
 * @author Tookie
 *
 * Server log level class for Logger
 *
 */
#include "ServerLogLevel.hh"

namespace logs
{
    ServerLogLevel::ServerLogLevel()
    {}

    ServerLogLevel::~ServerLogLevel()
    {}

    std::string ServerLogLevel::getLogLevelName() const
    {
        return logs::SERVER;
    }

    std::ostream& ServerLogLevel::getLogLevelStream()
    {
        return std::cout;
    }

    static ServerLogLevel serverLogLevel;
}
