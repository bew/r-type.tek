/**
 * @file CompWindow.hh
 * @author Nekhot.
 * @brief Component for entity that need there own windows.
 */

#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/VideoMode.hpp"
#include "ECS/AComponent.hh"

namespace ECS {
  namespace Component {

    static const std::string WINDOW = "window";

    /**
     * Component for window
     */
    class CompWindow : public AComponent {
    protected:
      /**
       * Is the window fullscreen
       */
      bool _fullscreen;
  
      /**
       * Window width in px
       */
      unsigned int _width;
  
      /**
       * Window height in px
       */
      unsigned int _height;
  
      /**
       * anti aliasing level
       */
      unsigned int _aaliasing;
  
      /**
       * Default name for the windows
       */
      std::string _title;

      /**
       * Has the configuratio changed (should be set in getter but i'm lazy)
       */
      bool _changed;

    public:

      bool getFullscreen(void) const;
      unsigned int getHeight(void) const;
      unsigned int getWidth(void) const;
      unsigned int getAAliasing(void) const;
      const std::string &getTitle(void) const;
      bool getChanged(void) const;

      void setFullscreen(bool);
      void setHeight(unsigned int);
      void setWidth(unsigned int);
      void setAAliasing(unsigned int);
      void setTitle(const std::string &);
      void setChanged(bool);
      
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

      /**
       * Underlying sfml window
       */
      sf::RenderWindow *window;

      /**
       * Default construtor
       */
      CompWindow(void);

      /**
       * @return ECS::Cmponent::WINDOW
       */
      virtual const std::string &getType() const;

      /**
       * Default Dtor
       */
      ~CompWindow(void);
    };
  }
}
