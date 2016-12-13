#include "MusicAsset.hh"

graphic::MusicAsset::MusicAsset(const std::string &path) {
  if (!_music.openFromFile(path))
      throw AssetException("Unable to load music from '" + path + "'");
}

const sf::Music &graphic::MusicAsset::getLowLevelMusic(void) const {
  return _music;
} 
