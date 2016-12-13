#include "SoundAsset.hh"

graphic::SoundAsset::SoundAsset(const std::string &path) {
  if (!_sound.loadFromFile(path))
      throw AssetException("Unable to load sound from '" + path + "'");
}

const sf::SoundBuffer &graphic::SoundAsset::getLowLevelSound(void) const {
  return _sound;
} 
