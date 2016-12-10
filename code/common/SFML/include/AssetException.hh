#ifndef _ASSETEXCEPTION_HPP
#define _ASSETEXCEPTION_HPP

#include <string>
#include <stdexcept>

namespace graphic {
  class AssetException : public std::runtime_error {
  public:
    AssetException(const std::string &);
  };
}

#endif
