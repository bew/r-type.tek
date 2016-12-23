/**
 * @file InfoLogLevel.hh
 * @brief Abstract for log level with file
 * @author Christopher Paccard
 *
 * Abstract class for a log level with a file
 *
 */

#include "Logger.hh"

namespace logs {
    ALogLevelFile::ALogLevelFile(const std::string& filename) {
        _logFile.open(filename, std::ofstream::out | std::ofstream::app);
        if (!_logFile.is_open())
            std::cerr << "Can't open log file: " << filename << std::endl;
    }

    ALogLevelFile::~ALogLevelFile() {
        if (_logFile.is_open())
            _logFile.close();
    }

    std::ostream &ALogLevelFile::getLogLevelStream() {
        return _logFile;
    }
}