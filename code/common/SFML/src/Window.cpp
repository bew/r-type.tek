#include "Window.hh"

const std::string graphic::Config::DEFAULT_TITLE = "Āru Taipu";
const unsigned int graphic::Config::DEFAULT_BPP = 32;
const unsigned int graphic::Config::DEFAULT_WIDTH = 800;
const unsigned int graphic::Config::DEFAULT_HEIGHT = 600;
const unsigned int graphic::Config::DEFAULT_AA = 0;
const bool graphic::Config::DEFAULT_FULLSCREEN = false;

graphic::Config::Config(void) :
  fullscreen(graphic::Config::DEFAULT_FULLSCREEN),
  width(graphic::Config::DEFAULT_WIDTH),
  height(graphic::Config::DEFAULT_HEIGHT),
  bpp(graphic::Config::DEFAULT_BPP),
  aaliasing(graphic::Config::DEFAULT_AA),
  title(graphic::Config::DEFAULT_TITLE)
{}

graphic::Window::Window(const graphic::Config &config)
{
  _window = nullptr;
  this->setConfig(config);
}

void graphic::Window::setConfig(const graphic::Config &config) {
  _config = config;
  sf::VideoMode mode(_config.width, _config.height, _config.bpp);
  unsigned int style;
  if (_config.fullscreen)
    style = sf::Style::Fullscreen;
  else
    style = sf::Style::Default;
  sf::ContextSettings ctx;
  ctx.antialiasingLevel = _config.aaliasing;
  if (_window != nullptr)
    delete _window;
  _window = new sf::RenderWindow(mode, _config.title, style, ctx);
}

graphic::Window::~Window(void) {
  delete _window;
}

const graphic::Config &graphic::Window::getConfig(void) const {
  return _config;
}

sf::RenderWindow &graphic::Window::getLowLevelWindow(void) {
  return *_window;
};
