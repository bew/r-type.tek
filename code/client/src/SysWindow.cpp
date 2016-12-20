/**
 * @file SysWindow.cpp
 * @author Nekhot.
 * @brief Impelmentation of system procesing windows.
 */

#include "SysWindow.hh"

namespace ECS {
  namespace System {

    void SysWindow::update(WorldData &world) {
      this->update(world._systemEntity);
    }
    
    void SysWindow::update(Entity::Entity &entity) {
      Component::CompWindow *wc = dynamic_cast<Component::CompWindow*>(entity.getComponent("window"));
      if (wc && (!wc->window || wc->changed)) {
	sf::VideoMode mode(wc->width, wc->height, wc->bpp);
	unsigned int style;
	if (wc->fullscreen)
	  style = sf::Style::Fullscreen;
	else
	  style = sf::Style::Default;
	sf::ContextSettings ctx;
	ctx.antialiasingLevel = wc->aaliasing;
	delete wc->window;
	wc->window = new sf::RenderWindow(mode, wc->title, style, ctx);
	wc->changed = false;
      }
    }
  }
}
