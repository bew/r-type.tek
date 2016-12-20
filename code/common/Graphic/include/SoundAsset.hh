/**
 * @file SoundAsset.hh
 * @brief Header for sound asset
 * @author Nekhot
 */

#pragma once

#include <string>
#include <SFML/Audio/SoundBuffer.hpp>

#include "AssetException.hh"

namespace graphic {

  /**
   * Wrapper for sound
   */
  class SoundAsset {
  public:
    /**
     * Construct a fontAsset
     *
     * @param path: the path of the file to open
     * @throw AssetException: if the music asset at path cannot be openned, or loaded
     */
    SoundAsset(const std::string &path);

    /**
     * Get the underlying sound asset
     *
     * @return the undeerlying music asset
     */
    const sf::SoundBuffer &getLowLevelSound(void) const;
  protected:
    /**
     * Underlying sound object
     */
    sf::SoundBuffer _sound;
  };
}
