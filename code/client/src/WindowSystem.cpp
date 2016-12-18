#include <iostream>
#include "WindowSystem.hh"

void WindowSystem::process(Entity &entity) {
  Component *raw = nullptr;
  try {
    std::cout << "PROCESSING WINDOW" << std::endl; 
    raw = entity.getComponent("window");
    WindowComponent &wc = *dynamic_cast<WindowComponent*>(raw);
    if (!wc.window) {
      sf::VideoMode mode(wc.width, wc.height, wc.bpp);
      unsigned int style;
      if (wc.fullscreen)
	style = sf::Style::Fullscreen;
      else
	style = sf::Style::Default;
      sf::ContextSettings ctx;
      ctx.antialiasingLevel = wc.aaliasing;
      delete wc.window;
      wc.window = new sf::RenderWindow(mode, wc.title, style, ctx);
    }
  } catch(const ECSException &e) {
    std::cout << "WINDOW COMPONENT NOT FOUND" << std::endl;
  }
}
