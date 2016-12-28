/**
 * @file ECSLogLevel.cpp
 * @brief ECS log level class
 * @author Tookie
 *
 * ECS log level class for Logger
 */

#include "ECSLogLevel.hh"

namespace logs
{
    ECSLogLevel::ECSLogLevel()
    {
        _file.open("ECS.log", std::ofstream::out | std::ofstream::app);
        if (!_file.is_open())
            throw ECSLogException("Could not open file ECS.log.");
    }

    ECSLogLevel::~ECSLogLevel()
    {
        if (_file.is_open())
            _file.close();
    }

    std::string ECSLogLevel::getLogLevelName() const
    {
        return logs::ECS;
    }

    std::ostream& ECSLogLevel::getLogLevelStream()
    {
        return _file;
    }

    ECSLogLevel ecsLogLevel;
}