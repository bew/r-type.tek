#ifndef _ANIMATEDSPRITEASSET_HPP
#define _ANIMATEDSPRIETASSET_HPP

#include <string>
#include <SFML/Graphics/Texture.hpp>

#include "Document.hh"
#include "Window.hh"
#inclued "Animation.hh"
#include "AssetException.hh"

#include "FORWARD.hh"

namespace graphic {

  /**
   * Hold all ressources necessary to drawing a frame from a spritemap 
   */
  class AnimatedSpriteAsset {
  public:
    
    /**
     * Construct an AnimatedSpriteAsset
     *
     * @param path: the path of the texturefile to open
     * @param animspecPath: the path of the BSON file holding information about the animations and frames 
     * @throw AssetException: if the sprite asset at path cannot be openned, or loaded
     */
    AnimatedSpriteAsset(const std::string &path, const std::string &animSpecPath);

    /**
     * Draw the current texture
     *
     * @param window: the window to draw the texture on
     * @param position: where to draw the texture
     * @param animation: the object used to determine which part of the texture to draw
     */
    void draw(graphic::Window &window, const world::position &position, const graphic::Animation &animation) const;
    
  protected:

    /**
     * The sfml texture object that hold the spritemap
     */
    sf::Texture _texture;

    /**
     * The bson document holding the animations specification. This will probably be replaced by a wrapper for quicker access to frame info.
     */
    bson::Document _animations;
  };
}

#endif
