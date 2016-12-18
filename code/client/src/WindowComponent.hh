#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/VideoMode.hpp"

#include "alpha.hpp"

class WindowComponent : public Component {
public:
  /**
   * Is the window fullscreen
   */
  bool fullscreen;
  
  /**
   * Window width in pc
   */
  unsigned int width;
  
  /**
   * Window height in px
   */
  unsigned int height;
  
  /**
   * bit per pixel
   */
  unsigned int bpp;
  
  /**
   * anti aliasing level
   */
  unsigned int aaliasing;
  
  /**
   * Default name for the windows
   */
  std::string title;
  
  /**
   * Default title
   */
  static const std::string DEFAULT_TITLE; 
  
  /**
   * Default bit per pixel rate
   */
  static const unsigned int DEFAULT_BPP;

  /**
   * Default width
   */
  static const unsigned int DEFAULT_WIDTH;
  
  /**
   * Default height
   */
  static const unsigned int DEFAULT_HEIGHT;
  
  /**
   * Default anti aliasing level 
   */
  static const unsigned int DEFAULT_AA;
  
  /**
   * Default fullscreen value
   */
  static const bool DEFAULT_FULLSCREEN;

  sf::RenderWindow *window;

  WindowComponent(void);
};
