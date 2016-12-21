/**
 * @file Logger.hh
 * @brief Class for Logger
 * @author Christopher Paccard
 *
 * Allow to log a lot of things
 *
 */

#ifndef LOGS_LOGGER_HH
#define LOGS_LOGGER_HH

#include <iostream>
#include <fstream>
#include <string>
#include <map>

/**
 * Contain logs stuff
 */
namespace logs {

    /**
     * Abstract class for a log level
     */
    class ALogLevel {
    public :
        /**
         * Ctor
         */
        ALogLevel(void) {}

        ALogLevel(const ALogLevel &aLogLevel);

        ALogLevel &operator=(const ALogLevel &aLogLevel);

        /**
         * Dtor
         */
        virtual ~ALogLevel() {}

        /**
         * Get the name of the log level
         *
         * @return the name of the log level
         */
        virtual std::string getLogLevelName(void) const = 0;

        /**
         * Get the stream of the log level to know where to write
         *
         * @return the stream of the log level to know where to write
         */
        virtual std::ostream &getLogLevelStream(void) = 0;
    };

    /**
     * Allow to log a lot of things
     */
    class Logger {
    private:
        /**
         * The line number displayed by the Logger
         */
        unsigned int _logNumber;

        /**
         * A global log file which store ALL the logs
         */
        std::ofstream _globalLogFile;

        /**
         * Store all the logs level which are provided by the function register
         */
        std::map<std::string, ALogLevel *> _logsLevel;

        /**
         * Store the last log level used
         */
        ALogLevel *_lastLogLevel;

    public:
        /**
         * Ctor
         */
        Logger();

        Logger(const Logger &logger) = delete;

        Logger &operator=(const Logger &logger) = delete;

        /**
         * Dtor
         */
        ~Logger();

        /**
         * Allow to register a log level inside the Logger in order to be used
         *
         * @param logLevel the log level to register in order to be used
         */
        void registerLogLevel(ALogLevel *logLevel);

        /**
         * Allow to unregister a log level inside the Logger
         *
         * @param logLevelName the name of the log level to unregister
         * @return true if there was a log level to unregister, else false
         */
        bool unregisterLogLevel(const std::string& logLevelName);

        /**
         * Create a new entry inside the logger and change the log level if required
         *
         * @param logLevelName the name of the log level to use for the new entry
         * @throw std::out_of_range if the logLevelName doesn't match any log level info register previously
         * @return the Logger in order to chain call for logging
         */
        Logger &logLevel(const std::string &logLevelName);

        /**
         * Allow to log everything that has an operator << with ostream
         *
         * @tparam T the type of the value logged
         * @param value the value to log
         * @return the Logger in order to chain calls
         */
        template<typename T>
        Logger &operator<<(const T &value) {
            if (_globalLogFile.is_open())
                _globalLogFile << value;
            _lastLogLevel->getLogLevelStream() << value;
            return *this;
        }

        /**
         * Allow to use features from ostream for logging purpose
         *
         * @param os the stream feature
         * @return the Logger in order to chain calls
         */
        Logger &operator<<(std::ostream &(*os)(std::ostream &)) {
            if (_globalLogFile.is_open())
                _globalLogFile << os;
            _lastLogLevel->getLogLevelStream() << os;
            return *this;
        }

    };

    /**
     * Singleton of Logger
     */
    extern Logger logger;
};

#endif //LOGS_LOGGER_HH
