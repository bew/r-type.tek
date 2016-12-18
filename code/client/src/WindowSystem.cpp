#include "WindowSystem.hh"

void WindowSystem::process(Entity &entity) {
  try {
    WindowComponent &wc = dynamic_cast<WindowComponent*>(entity.getComponent("window"));
    if (!wc.window) {
      sf::VideoMode mode(wc.width, wc.height, wc.bpp);
      unsigned int style;
      if (fullscreen)
	style = sf::Style::Fullscreen;
      else
	style = sf::Style::Default;
      sf::ContextSettings ctx;
      ctx.antialiasingLevel = wc.aaliasing;
      delete wc.window;
      wc.window = new sf::RenderWindow(mode, wc.title, style, ctx);
    }
  } catch(const ECSException &e) {
  }
}
