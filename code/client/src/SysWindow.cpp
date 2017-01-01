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
            Component::CompWindow *wc = dynamic_cast<Component::CompWindow *>(entity.getComponent(
                    ECS::Component::WINDOW));
            Component::CompOptions *optionsc = dynamic_cast<Component::CompOptions *>(entity.getComponent(
                    ECS::Component::OPTIONS));

            if (optionsc && wc && (!wc->window)) {
                sf::VideoMode mode(optionsc->getWidth(), optionsc->getHeight(),
                                   ECS::Component::CompWindow::DEFAULT_BPP);
                unsigned int style;
                if (optionsc->getFullscreen())
                    style = sf::Style::Fullscreen;
                else
                    style = sf::Style::Default;
                sf::ContextSettings ctx;
                ctx.antialiasingLevel = optionsc->getAAliasing();
                delete wc->window;
                wc->window = new sf::RenderWindow(mode, optionsc->getTitle(), style, ctx);
                wc->window->setView(sf::View(sf::Rect<float>(0, 0, ECS::Component::XMAX, ECS::Component::YMAX)));
            }
        }
    }
}
