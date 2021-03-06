/**
 * @file SpriteAsset.hh
 * @brief Header sprite text asset
 * @author Nekhot
 */

#pragma once

#include <string>
#include "SFML/Graphics/Texture.hpp"

#include "AssetException.hh"

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
     * @throw AssetException: if the sprite asset at path cannot be opened, or loaded
     */
    SpriteAsset(const std::string &path);

    /**
     * Return the wrapped texture
     *
     * @return the texture
     */
    const sf::Texture &getLowLevelTexture(void) const;
    
  protected:
    /**
     * The sfml texture object that hold the spritemap
     */
    sf::Texture _texture;
  };
}
