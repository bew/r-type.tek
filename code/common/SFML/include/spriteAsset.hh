#ifndef _SPTITEASSET_HPP
#define _SPRITEASSET_HPP

#include <string>
#include <SFML/Texture.hpp>

#include "assetException.hpp"

class SpriteAsset {
public:
  /**
   * Construct a fontAsset
   *
   * @param path: the path of the file to open
   * @throw AssetException: if the sprite asset at path cannot be openned, or loaded
   */
  SpriteAsset(const std::string &path);
protected:
  sf::Texture _texture;
};

#endif
