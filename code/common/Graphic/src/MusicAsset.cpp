/**
 * @file MusicAsset.cpp
 * @brief Implementation for music store
 * @author Nekhot
 */

#include "MusicAsset.hh"

graphic::MusicAsset::MusicAsset(const std::string &path) {
  if (!_music.openFromFile(path))
      throw AssetException("Unable to load music from '" + path + "'");
}

sf::Music &graphic::MusicAsset::getLowLevelMusic(void) {
  return _music;
} 
