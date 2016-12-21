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
      Component::CompWindow *wc = dynamic_cast<Component::CompWindow*>(entity.getComponent(ECS::Component::WINDOW));
      if (wc && (!wc->window || wc->getChanged())) {
	sf::VideoMode mode(wc->getWidth(), wc->getHeight(), ECS::Component::CompWindow::DEFAULT_BPP);
	unsigned int style;
	if (wc->getFullscreen())
	  style = sf::Style::Fullscreen;
	else
	  style = sf::Style::Default;
	sf::ContextSettings ctx;
	ctx.antialiasingLevel = wc->getAAliasing();
	delete wc->window;
	wc->window = new sf::RenderWindow(mode, wc->getTitle(), style, ctx);
	wc->setChanged(false);
      }
    }
  }
}
