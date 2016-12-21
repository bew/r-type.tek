/**
 * @file InfoLogLevel.hh
 * @brief Info log level class
 * @author Christopher Paccard
 *
 * Info log level class for Logger
 *
 */

#ifndef LOGS_INFOLOGLEVEL_HH
#define LOGS_INFOLOGLEVEL_HH

#include "Logger.hh"

/**
 * Contain logs stuff
 */
namespace logs {
    /**
     * Represent the name of the info log level
     */
    static const std::string INFO = "Info";

    /**
     * Info log level class for Logger
     */
    class InfoLogLevel : public ALogLevel {
    public:
        /**
         * Ctor
         */
        InfoLogLevel(void);

        InfoLogLevel(const InfoLogLevel &infoLogLevel) = delete;

        InfoLogLevel &operator=(const InfoLogLevel &infoLogLevel) = delete;

        /**
         * Dtor
         */
        virtual ~InfoLogLevel();

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

#endif //LOGS_INFOLOGLEVEL_HH
