#ifndef _MUSICASSET_HPP
#define _MUSICASSET_HPP

#include <string>
#include <SFML/Audio/Music.hpp>

#include "AssetException.hh"

namespace graphic {

  /**
   * Wrapper for music
   */
  class MusicAsset {
  public:
    /**
     * Construct a fontAsset
     *
     * @param path: the path of the file to open
     * @throw AssetException: if the music asset at path cannot be openned, or loaded
     */
    MusicAsset(const std::string &path);

    /**
     * Get the underlying music asset
     *
     * @return the undeerlying music asset
     */
    const sf::Music &getLowLevelMusic(void) const;
  protected:
    /**
     * Undelying music object
     */
    sf::Music _music;
  };
}

#endif
