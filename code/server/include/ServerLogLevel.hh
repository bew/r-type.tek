/**
 * @file ServerLogLevel.hh
 * @brief Server log level class
 * @author Tookie
 *
 * Server log level class for Logger
 *
 */

#pragma once

#include "Logger.hh"
#include <fstream>
#include <string>
#include <stdexcept>

/**
 * Contain logs stuff
 */
namespace logs
{
    /**
     * Represent the name of the debug log level
     */
    static const std::string SERVER = "server";

    /**
     * represents a server log, he's throw when log error occured
     */
    using ServerLogException = std::runtime_error;

    /**
     * Server log level class for Logger
     */
    class ServerLogLevel : public ALogLevel
    {
    public:
        /**
         * constructor of ServerLogLevel
         */
        ServerLogLevel();

        /**
         * Destructor
         */
        virtual ~ServerLogLevel();

        /**
         * Get the name of the log level
         *
         * @return the name of the log level
         */
        virtual std::string getLogLevelName() const;

        /**
         * Get the stream of the log level to know where to write
         *
         * @return the stream of the log level to know where to write
         */
        virtual std::ostream &getLogLevelStream();

    private:
        /**
         * represents the file stream for log inside
         */
        std::ofstream _file;
    };

}
