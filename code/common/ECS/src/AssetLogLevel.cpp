/**
 * @file AssetLogLevel.cpp
 * @brief Asset log level class
 * @author Nekhot
 *
 * Asset log level class for Logger
 *
 */

#include "AssetLogLevel.hh"

namespace logs {
    AssetLogLevel::AssetLogLevel() {
    }

    AssetLogLevel::~AssetLogLevel() {
    }

    std::string AssetLogLevel::getLogLevelName() const {
        return logs::ASSET;
    }

    std::ostream &AssetLogLevel::getLogLevelStream() {
        return std::cerr;
    }

    AssetLogLevel assetLogLevel;
}
