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
    {
        _file.open("server.log", std::ofstream::out | std::ofstream::app);
        if (!_file.is_open())
            throw ServerLogException("Could not open file server.log.");
    }

    ServerLogLevel::~ServerLogLevel()
    {
        if (_file.is_open())
            _file.close();
    }

    std::string ServerLogLevel::getLogLevelName() const
    {
        return logs::SERVER;
    }

    std::ostream& ServerLogLevel::getLogLevelStream()
    {
        return std::cerr;
    }

    static ServerLogLevel serverLogLevel;
}
