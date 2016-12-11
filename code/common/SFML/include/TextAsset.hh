#ifndef _TEXTASSET_HPP
#define _TEXTASSET_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <SFML/Graphics/Color.hpp>

#include "AssetException.hh"
#include "Window.hh"
#include "FontAsset.hh"

namespace graphic {

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

    float thickness;
    unsigned int size;
    sf::Color fill;
    sf::Color out;
    static const sf::Color DEFAULT_FILL;
    static const sf::Color DEFAULT_OUT;
    static const unsigned int DEFAULT_SIZE;
    static const float DEFAULT_THICKNESS;
  };
  
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
    std::string *_text;
  };
}

#endif
