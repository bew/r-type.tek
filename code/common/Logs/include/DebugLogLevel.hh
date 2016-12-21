/**
 * @file DebugLogLevel.hh
 * @brief Debug log level class
 * @author Christopher Paccard
 *
 * Debug log level class for Logger
 *
 */

#ifndef LOGS_DEBUGLOGLEVEL_HH
#define LOGS_DEBUGLOGLEVEL_HH

#include "Logger.hh"

/**
 * Contain logs stuff
 */
namespace logs {
    /**
     * Represent the name of the debug log level
     */
    static const std::string DEBUG = "Debug";

    /**
     * Debug log level class for Logger
     */
    class DebugLogLevel : public ALogLevel {
    public:
        /**
         * Ctor
         */
        DebugLogLevel(void);

        DebugLogLevel(const DebugLogLevel &debugLogLevel) = delete;

        DebugLogLevel &operator=(const DebugLogLevel &debugLogLevel) = delete;

        /**
         * Dtor
         */
        virtual ~DebugLogLevel();

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
        virtual std::ostream &getLogLevelStream(void) const;
    };
}

#endif //LOGS_DEBUGLOGLEVEL_HH
