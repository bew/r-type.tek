#include "SpriteAsset.hh"

graphic::SpriteAsset::SpriteAsset(const std::string &path)
{
  if (!_texture.loadFromFile(path))
    throw AssetException("Unable to load asset : '" + path + "'");
}

void graphic::SpriteAsset::draw(graphic::Window &window, const world::Position &position) const {
  sf::RenderWindow &target = window.getLowLevelWindow();
  sf::Sprite surface(_texture);
  surface.setPosition(static_cast<float>(position.x), static_cast<float>(position.y));
  target.draw(surface);
}
