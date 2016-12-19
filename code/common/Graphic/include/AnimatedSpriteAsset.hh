#ifndef _ANIMATEDSPRITEASSET_HPP
#define _ANIMATEDSPRIETASSET_HPP

#include <string>
#include <vector>
#include <iterator>
#include <fstream>
#include <unordered_map>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "BSON/Document.hh"
#include "AssetException.hh"

namespace graphic {

  /**
   * Hold all ressources necessary to drawing a frame from a spritemap 
   */
  class AnimatedSpriteAsset {
  public:

    /**
     * Contain public information about a single animations
     */
    struct FrameDescriptions {
      /**
       * The animation frequency
       */
      double frequency;
      /**
       * The reactangles of each frame if the animation
       */
      std::vector<sf::Rect<int>> frames;
    };
    
    /**
     * Construct an AnimatedSpriteAsset
     *
     * @param path: the path of the texturefile to open
     * @param animspecPath: the path of the BSON file holding information about the animations and frames 
     * @throw AssetException: if the sprite asset at path cannot be openned, or loaded
     */
    AnimatedSpriteAsset(const std::string &path, const std::string &animSpecPath);

    /**
     * Get the wrapped sf::texture
     *
     * @return : the wrapped texture
     */
    const sf::Texture &getLowLevelTexture(void) const;

    /**
     * Get the animations specifications
     *
     * @return : the animations specification
     */
    const std::unordered_map<std::string, graphic::AnimatedSpriteAsset::FrameDescriptions> &getAnimations(void) const;
    
  protected:

    /**
     * The sfml texture object that hold the spritemap
     */
    sf::Texture _texture;

    /**
     * The bson document holding the animations specification. This will probably be replaced by a wrapper for quicker access to frame info.
     */
    std::unordered_map<std::string, graphic::AnimatedSpriteAsset::FrameDescriptions> _animations;
  };
}

#endif
