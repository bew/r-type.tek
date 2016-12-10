#ifndef _MUSICASSET_HPP
#define _MUSICASSET_HPP

#include <string>
#include <SFML/Sound.hpp>

#include "assetException.hpp"

class MusicAsset {
public:
  /**
   * Construct a fontAsset
   *
   * @param path: the path of the file to open
   * @throw AssetException: if the sound asset at path cannot be openned, or loaded
   */
  SoundAsset(const std::string &path);
protected:
  sf::Sound _sound;
};

#endif
