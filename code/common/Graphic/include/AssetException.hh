/**
 * @file AssetException.hh
 * @brief Header for asset exception
 * @author Nekhot
 */

#pragma once

#include <string>
#include <stdexcept>

namespace graphic {
  /**
   * Exception throw in case of error loading or using asset 
   */
  class AssetException : public std::runtime_error {
  public:
    /**
     * Constructor with a message
     *
     * @param e: the error and why it happen
     */
    AssetException(const std::string &e);
  };
}
