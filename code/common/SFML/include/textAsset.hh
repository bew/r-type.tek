#ifndef _TEXTASSET_HPP
#define _TEXTASSET_HPP

#include <string>
#include "assetException.hpp"

class TextAsset {
public:
  /**
   * Construct a textAsset
   *
   * @param path: the path of the fiel to open
   * @throw AssetException: if the text asset at path cannot be openned
   */
  TextAsset(const std::string &path);
  const std::string &getText(void) const;
protected:
  std::string _text;
};

#endif
