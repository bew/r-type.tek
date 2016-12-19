#include "SpriteAsset.hh"

graphic::SpriteAsset::SpriteAsset(const std::string &path)
{
  if (!_texture.loadFromFile(path))
    throw AssetException("Unable to load sprite asset : '" + path + "'");
}

const sf::Texture &graphic::SpriteAsset::getLowLevelTexture(void) const {
  return _texture;
};
