#ifndef _SOUNDASSET_HPP
#define _SOUNDASSET_HPP

#include <string>
#include <SFML/Audio/SoundBuffer.hpp>

#include "AssetException.hh"

namespace graphic {
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
    sf::SoundBuffer _sound;
  };
}

#endif
