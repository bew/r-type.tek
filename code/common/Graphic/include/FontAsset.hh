#ifndef _FONTASSET_HPP
#define _FONTASSET_HPP

#include <string>
#include <SFML/Graphics/Font.hpp>

#include "AssetException.hh"

namespace graphic {

  /**
   * Wrapper for font
   */
  class FontAsset {
  public:
    /**
     * Construct a fontAsset
     *
     * @param path: the path of the file to open
     * @throw AssetException: if the font asset at path cannot be openned, or loaded
     */
    FontAsset(const std::string &path);

    /**
     * Get the wrapped sf::Font
     *
     * @return : the wrapped font
     */
    const sf::Font &getLowLevelFont(void) const;
  protected:
    /**
     * Underlying font object
     */
    sf::Font _font;
  };
}

#endif
