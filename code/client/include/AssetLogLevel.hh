/**
 * @file AssetLogLevel.hh
 * @brief Asset log level class
 * @author Nekhot
 */

#pragma once

#include "Logs/Logger.hh"

/**
 * Contain logs stuff
 */
namespace logs {
    /**
     * Represent the name of the error log level
     */
    static const std::string ASSET = "Asset";

    /**
     * Asset log level class for Logger
     */
    class AssetLogLevel : public ALogLevel {
    public:
        /**
         * Ctor
         */
        AssetLogLevel(void);

        AssetLogLevel(const AssetLogLevel &errorLogLevel) = delete;

        AssetLogLevel &operator=(const AssetLogLevel &errorLogLevel) = delete;

        /**
         * Dtor
         */
        virtual ~AssetLogLevel();

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

  extern AssetLogLevel assetLogLevel;
}
