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
      
      if (wc && (!wc->window)) {
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
	wc->window->setView(sf::View(sf::Rect<float>(0, 0, ECS::Component::XMAX, ECS::Component::YMAX)));
      }
      else if (wc) {
	sf::Event event;
	Component::CompTick *tickc = dynamic_cast<Component::CompTick*>(entity.getComponent(ECS::Component::TICK));
	if (tickc) {
	  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
	    wc->window->close();
	    tickc->kill = true;
	  }
	  else
	    while (wc->window->pollEvent(event)) {
	      if (event.type == sf::Event::Closed) {
		wc->window->close();
		tickc->kill = true;
	      }
	    }
	}
	wc->window->display();
	wc->window->clear(sf::Color::Black);
      }
      if (wc->_changed) {
	Component::CompEvent *eventc = dynamic_cast<Component::CompEvent*>(entity.getComponent(ECS::Component::EVENT));
	if (eventc)
	  eventc->addEvent("window_update", nullptr);
	wc->_changed = false;
      }
    }
  }
}
