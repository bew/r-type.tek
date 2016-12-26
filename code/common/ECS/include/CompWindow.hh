/**
 * @file CompWindow.hh
 * @author Nekhot.
 * @brief Component for entity that need there own windows.
 */

#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/VideoMode.hpp"
#include "SFML/Window.hpp"
#include "AComponent.hh"

namespace ECS {
  namespace Component {

    static const std::string WINDOW = "window";

    /**
     * Component for window
     */
    class CompWindow : public AComponent {
    protected:
    public:
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

      static const int DEFAULT_BPP;
    };
  }
}
