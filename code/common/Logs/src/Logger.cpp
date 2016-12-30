/**
 * @file Logger.cc
 * @brief Class for Logger
 * @author Christopher Paccard
 *
 * Allow to log a lot of things
 *
 */

#include <sstream>
#include <chrono>
#include <iomanip>
#include "Logger.hh"

namespace logs {

    Logger::Logger() : _logNumber(0) {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        std::stringstream filenameDate;
        filenameDate << std::put_time(std::localtime(&in_time_t), "%d-%m-%Y_%H-%M-%S");

        std::string fileName = std::string("logs/r-type_") + filenameDate.str() + std::string(".log");
        _globalLogFile.open(fileName, std::ofstream::out | std::ofstream::app);

        if (!_globalLogFile.is_open()) {
            std::cerr << "Impossible to write into global logs file: " << fileName << std::endl;
            std::cerr << "Please create the folder if it doesn't exist or check the rights of it" << std::endl;
        }
    }

    Logger::~Logger() {
        if (_globalLogFile.is_open())
            _globalLogFile.close();
    }

    void Logger::registerLogLevel(ALogLevel *logLevel) {
        _logsLevel[logLevel->getLogLevelName()] = logLevel;
    }

    void Logger::registerBasicsLogLevel() {
        this->registerLogLevel(&logs::infoLogLevel);
        this->registerLogLevel(&logs::errorLogLevel);
        this->registerLogLevel(&logs::debugLogLevel);
    }

    bool Logger::unregisterLogLevel(const std::string &logLevelName) {
        return _logsLevel.erase(logLevelName) > 0;
    }

    bool Logger::isRegister(const std::string &logLevelName) const {
        return _logsLevel.count(logLevelName) > 0;
    }

    Logger &Logger::logLevel(const std::string &logLevelName) {
        ALogLevel *logLevel = _logsLevel.at(logLevelName);

        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        std::stringstream date;
        date << std::put_time(std::localtime(&in_time_t), "%c");

        std::string header = std::to_string(_logNumber) + std::string(" <") + date.str() +
                             std::string("> ~ [") + logLevel->getLogLevelName() + std::string("] : ");

        if (_globalLogFile.is_open())
            _globalLogFile << header;
        logLevel->getLogLevelStream() << header;

        ++_logNumber;

        _lastLogLevel = logLevel;
        return *this;
    }

    Logger& Logger::operator[](const std::string &logLevelName) {
        return this->logLevel(logLevelName);
    }

    static Logger *logger = nullptr;

    Logger& getLogger(void) {
        if (logger == nullptr)
            logger = new Logger;
        return *logger;
    }

    bool deleteLogger(void) {
        if (logger != nullptr) {
            delete logger;
            return true;
        }
        return false;
    }
}
