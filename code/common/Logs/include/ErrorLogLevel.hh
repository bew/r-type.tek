/**
 * @file ErrorLogLevel.hh
 * @brief Error log level class
 * @author Christopher Paccard
 *
 * Error log level class for Logger
 *
 */

#ifndef LOGS_ERRORLOGLEVEL_HH
#define LOGS_ERRORLOGLEVEL_HH

#include "Logger.hh"

/**
 * Contain logs stuff
 */
namespace logs {
    /**
     * Represent the name of the error log level
     */
    static const std::string ERRORS = "Error";

    /**
     * Error log level class for Logger
     */
    class ErrorLogLevel : public ALogLevel {
    public:
        /**
         * Ctor
         */
        ErrorLogLevel(void);

        ErrorLogLevel(const ErrorLogLevel &errorLogLevel) = delete;

        ErrorLogLevel &operator=(const ErrorLogLevel &errorLogLevel) = delete;

        /**
         * Dtor
         */
        virtual ~ErrorLogLevel();

        /**
         * Get the name of the log level
         *
         * @return the name of the log level
         */
        virtual std::string getLogLevelName(void) const;

        /**
         * Get the stream of the log level to know where to write
         *
         * @return the stream of the log level to know where to write
         */
        virtual std::ostream &getLogLevelStream(void);
    };

    /**
     * Singleton of ErrorLogLevel
     */
    extern ErrorLogLevel errorLogLevel;
}

#endif //LOGS_ERRORLOGLEVEL_HH
