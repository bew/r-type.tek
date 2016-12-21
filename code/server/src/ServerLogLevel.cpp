//
// Created by tookie on 12/21/16.
//

#include "ServerLogLevel.hh"

namespace logs
{
    ServerLogLevel::ServerLogLevel()
    {
        _file.open("server.log", std::ofstream::out | std::ofstream::app);
        if (!_file.is_open())
            throw ServerLogException("Could not open file server.log.");
  //      logger.registerLogLevel(this);
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
        return _file;
    }

    static ServerLogLevel serverLogLevel;
}