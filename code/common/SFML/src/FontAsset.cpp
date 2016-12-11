#include "FontAsset.hh"

graphic::FontAsset::FontAsset(const std::string &path) {
  if (!_font.loadFromFile(path))
    throw AssetException("Unable to load font from asset '" + path + "'");
}

const sf::Font &graphic::FontAsset::getLowLevelFont(void) const {
  return _font;
}
