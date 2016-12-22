/**
 * @file CompWindow.cpp
 * @author Nekhot.
 * @brief Implementation of Component for entity that need there own windows.
 */

#include "CompWindow.hh"

namespace ECS {
  namespace Component {

    CompWindow::CompWindow(void) :
      _fullscreen(DEFAULT_FULLSCREEN),
      _width(DEFAULT_WIDTH),
      _height(DEFAULT_HEIGHT),
      _aaliasing(DEFAULT_AA),
      _title(DEFAULT_TITLE),
      _changed(false),
      window(nullptr)
    {};

    bool CompWindow::getFullscreen(void) const {
      return _fullscreen;
    };

    unsigned int CompWindow::getHeight(void) const {
      return _height;
    };

    unsigned int CompWindow::getWidth(void) const {
      return _width;
    };

    unsigned int CompWindow::getAAliasing(void) const {
      return _aaliasing;
    };
    
    const std::string &CompWindow::getTitle(void) const {
      return _title;
    };
    
    void CompWindow::setFullscreen(bool fullscreen) {
      if (_fullscreen != fullscreen)
        _changed = true;
      _fullscreen = fullscreen;
    };

    void CompWindow::setHeight(unsigned int height) {
      if (_height != height)
	_changed = true;
      _height = height;
    };
    
    void CompWindow::setWidth(unsigned int width) {
      if (_width != width)
	_changed = true;
      _width = width;
    };

    void CompWindow::setAAliasing(unsigned int aaliasing) {
      if (_aaliasing != aaliasing)
	_changed = true;
      _aaliasing = aaliasing;
    };

    void CompWindow::setTitle(const std::string &title) {
      if (_title != title)
	_changed = true;
      _title = title;
    };
    
    const std::string CompWindow::DEFAULT_TITLE = "Aru Taipu";
    const unsigned int CompWindow::DEFAULT_BPP = 32;
    const unsigned int CompWindow::DEFAULT_WIDTH = 1280;
    const unsigned int CompWindow::DEFAULT_HEIGHT = 720;
    const unsigned int CompWindow::DEFAULT_AA = 0;
    const bool CompWindow::DEFAULT_FULLSCREEN = false;

    const std::string &CompWindow::getType() const {
      return Component::WINDOW;
    }

    CompWindow::~CompWindow(void) {
      delete window;
    }
  }  
}
