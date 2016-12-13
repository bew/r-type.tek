#ifndef _FONTASSET_HPP
#define _FONTASSET_HPP

#include <string>
#include <SFML/Font.hpp>

#include "assetException.hpp"

class FontAsset {
public:
  /**
   * Construct a fontAsset
   *
   * @param path: the path of the file to open
   * @throw AssetException: if the font asset at path cannot be openned, or loaded
   */
  FontAsset(const std::string &path);
protected:
  sf::Font _font;
};

#endif
