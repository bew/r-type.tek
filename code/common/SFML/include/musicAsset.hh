#ifndef _MUSICASSET_HPP
#define _MUSICASSET_HPP

#include <string>
#include <SFML/Music.hpp>

#include "assetException.hpp"

class MusicAsset {
public:
  /**
   * Construct a fontAsset
   *
   * @param path: the path of the file to open
   * @throw AssetException: if the music asset at path cannot be openned, or loaded
   */
  MusicAsset(const std::string &path);
protected:
  sf::Music _music;
};

#endif
