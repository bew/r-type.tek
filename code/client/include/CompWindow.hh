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

    public:
      /**
       * Has the configuration changed
       */
      bool _changed;

      /**
       * @return Getter
       */
      bool getFullscreen(void) const;

      /**
       * @return Getter
       */
      unsigned int getHeight(void) const;

      /**
       * @return Getter
       */
      unsigned int getWidth(void) const;

      /**
       * @return Getter
       */
      unsigned int getAAliasing(void) const;

      /**
       * @return Getter
       */
      const std::string &getTitle(void) const;

      /**
       * @param ... Setter, will also set changed to true
       */
      void setFullscreen(bool);

      /**
       * @param ... Setter, will also set changed to true
       */
      void setHeight(unsigned int);

      /**
       * @param ... Setter, will also set changed to true
       */
      void setWidth(unsigned int);

      /**
       * @param ... Setter, will also set changed to true
       */
      void setAAliasing(unsigned int);

      /**
       * @param ... Setter, will also set changed to true
       */
      void setTitle(const std::string &);

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
