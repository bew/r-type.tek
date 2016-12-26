/**
 * @file ECSLogLevel.hh
 * @brief ECS log level class
 * @author Tookie
 *
 * ECS log level class for Logger
 */

#pragma once

#include <stdexcept>
#include <fstream>
#include "Logs/Logger.hh"

/**
 * Contain logs stuff
 */
namespace logs
{

    /**
     * Represent the name of the debug log level
     */
    static const std::string ECS = "ECS";

    /**
     * represents a ecs log exception, he's throw when log error occured
     */
    using ECSLogException = std::runtime_error;

    /**
     * ECS log level class for Logger
     */
    class ECSLogLevel
    {
    public:
        /**
         * Constructor of ECSLogLevel
         */
        ECSLogLevel();

        /**
         * destructor of ECSLogLevel
         */
        virtual ~ECSLogLevel();

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
        virtual std::ostream& getLogLevelStream();

    private:
        /**
         * represents the file stream for log inside
         */
        std::ofstream _file;
    };

}