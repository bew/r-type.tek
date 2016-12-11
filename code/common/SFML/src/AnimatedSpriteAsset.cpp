#include "AnimatedSpriteAsset.hh"

graphic::AnimatedSpriteAsset::AnimatedSpriteAsset(const std::string &path, const std::string &animSpecPath) {
    if (!_texture.loadFromFile(path))
    throw AssetException("Unable to load asset : '" + path + "'");
}
