#include "CompWindow.hh"

namespace ECS {
  namespace Component {

    CompWindow::CompWindow(void) :
      AComponent("window"),
      fullscreen(DEFAULT_FULLSCREEN),
      width(DEFAULT_WIDTH),
      height(DEFAULT_HEIGHT),
      bpp(DEFAULT_BPP),
      aaliasing(DEFAULT_AA),
      title(DEFAULT_TITLE),
      window(nullptr)
    {};

    const std::string CompWindow::DEFAULT_TITLE = "Āru Taipu";
    const unsigned int CompWindow::DEFAULT_BPP = 32;
    const unsigned int CompWindow::DEFAULT_WIDTH = 800;
    const unsigned int CompWindow::DEFAULT_HEIGHT = 600;
    const unsigned int CompWindow::DEFAULT_AA = 0;
    const bool CompWindow::DEFAULT_FULLSCREEN = false;
  }
}
