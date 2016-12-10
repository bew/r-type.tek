#include <SFML/Graphics.hpp>
#include "Window.hh"
#include "SpriteAsset.hh"
#include "AssetException.hh"

int main(void) {
  graphic::SpriteAsset s("img_test.bmp");
  graphic::Config cfg;
  graphic::Window window(cfg);
  world::Position p;
  p.x = 300;
  p.y = 300;
  
  while (window.getLowLevelWindow().isOpen())
    {
      sf::Event event;
      while (window.getLowLevelWindow().pollEvent(event))
	if (event.type == sf::Event::Closed)
	  window.getLowLevelWindow().close();
      window.getLowLevelWindow().clear();
      s.draw(window, p);
      window.getLowLevelWindow().display();
    }
}
