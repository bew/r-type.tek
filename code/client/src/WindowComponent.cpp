#include "WindowComponent.hh"

WindowComponent::WindowComponent(void) :
  Component("window"),
  fullscreen(DEFAULT_FULLSCREEN),
  width(DEFAULT_WIDTH),
  height(DEFAULT_HEIGHT),
  bpp(DEFAULT_BPP),
  aaliasing(DEFAULT_AA),
  title(DEFAULT_TITLE),
  window(nullptr)
{};

const std::string WindowComponent::DEFAULT_TITLE = "Āru Taipu";
const unsigned int WindowComponent::DEFAULT_BPP = 32;
const unsigned int WindowComponent::DEFAULT_WIDTH = 800;
const unsigned int WindowComponent::DEFAULT_HEIGHT = 600;
const unsigned int WindowComponent::DEFAULT_AA = 0;
const bool WindowComponent::DEFAULT_FULLSCREEN = false;

