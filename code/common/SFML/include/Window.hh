#ifndef WINDOW_HH
#define WINDOW_HH

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>

namespace graphic {

  struct Config {
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
     *
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

    /**
     * Default ctor
     */
    Config(void);
  };
  
  class Window {
  public:
    /**
     * Construct and open a windows
     *
     * @param config The window configuration
     */
    Window(const graphic::Config &);

    ~Window(void);

    /**
     * @return The current window configuration
     */
    const graphic::Config &getConfig(void) const;

    /**
     * @param config Set the configuration for the windows. May cause closing and reopening of the windows.
     */
    void setConfig(const graphic::Config&);

    /**
     * @return The sfml Windows
     */
    sf::RenderWindow &getLowLevelWindow(void);

  protected:
    /**
     * The current window configuration
     */
    graphic::Config _config;
    
    /**
     * The low level windows
     */
    sf::RenderWindow *_window;
  };
}

#endif
