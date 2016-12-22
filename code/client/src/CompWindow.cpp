/**
 * @file CompWindow.cpp
 * @author Nekhot.
 * @brief Implementation of Component for entity that need there own windows.
 */

#include "CompWindow.hh"

namespace ECS {
  namespace Component {

    CompWindow::CompWindow(void) :
      window(nullptr)
    {};
    
    const std::string &CompWindow::getType() const {
      return Component::WINDOW;
    }

    CompWindow::~CompWindow(void) {
      delete window;
    }

    const int CompWindow::DEFAULT_BPP = 4;
  }  
}
