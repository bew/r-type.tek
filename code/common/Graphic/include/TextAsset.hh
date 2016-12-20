/**
 * @file TextAsset.hh
 * @brief Header for text asset
 * @author Nekhot
 */

#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <SFML/Graphics/Color.hpp>

#include "AssetException.hh"
#include "FontAsset.hh"

namespace graphic {

  /**
   * Contain all public information about to draw a piece of text
   */
  class TextStyle {
  public:
    TextStyle(void);
    /**
     * Set fill color
     *
     * @param r: red value
     * @param g: green value
     * @param b: blue value
     * @param a: alpha value
     */
    void setFill(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    
    /**
     * Set out color
     *
     * @param r: red value
     * @param g: green value
     * @param b: blue value
     * @param a: alpha value
     */
    void setOut(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

    /**
     * Text thickness
     */
    float thickness;
    /**
     * Text size
     */
    unsigned int size;

    /**
     * Color of the text filling
     */
    sf::Color fill;
    /**
     * Color of the text outline
     */
    sf::Color out;

    /**
     * Default color for filling
     */
    static const sf::Color DEFAULT_FILL;

    /**
     * Default colro fot outline
     */
    static const sf::Color DEFAULT_OUT;

    /**
     * Default color for text size
     */
    static const unsigned int DEFAULT_SIZE;

    /**
     * Default color for text thickness
     */
    static const float DEFAULT_THICKNESS;
  };

  /**
   * Contain a text asset
   */
  class TextAsset {
  public:
    /**
     * Construct a textAsset
     *
     * @param path: the path of the fiel to open
     * @throw AssetException: if the text asset at path cannot be openned
     */
    TextAsset(const std::string &path);

    /*
     * Default dtor
     */
    ~TextAsset(void);
    
    /**
     * Get the stored text
     *
     * @return the stored text 
     */
    const std::string &getText(void) const;

  protected:
    /**
     * The text itself
     */
    std::string *_text;
  };
}
