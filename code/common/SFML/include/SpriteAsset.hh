#ifndef _SPRITEASSET_HPP
#define _SPRIETASSET_HPP

#include <string>
#include <SFML/Graphics/Texture.hpp>

#include "Window.hh"
#include "AssetException.hh"

#include "FORWARD.hh"

namespace graphic {

  /**
   * Hold all ressources necessary to drawing a sprite 
   */
  class SpriteAsset {
  public:
    
    /**
     * Construct an SpriteAsset
     *
     * @param path: the path of the texturefile to open 
     * @throw AssetException: if the sprite asset at path cannot be openned, or loaded
     */
    SpriteAsset(const std::string &path);

    /**
     * Draw the current texture
     *
     * @param window: the window to draw the texture on
     * @param position: where to draw the texture
     */
    void draw(graphic::Window &window, const world::Position &position) const;
    
  protected:
    /**
     * The sfml texture object that hold the spritemap
     */
    sf::Texture _texture;
  };
}

#endif
