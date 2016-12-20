/**
 * @file AssetException.cpp
 * @brief Implementation for asset exception
 * @author Nekhot
 */

#include "AssetException.hh"

graphic::AssetException::AssetException(const std::string &e) :
  std::runtime_error(e)
{};
