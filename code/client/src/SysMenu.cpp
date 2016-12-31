//
// Created by heuse on 23/12/2016.
//

#include "SysMenu.hh"
#include "ECS/World.hh"

namespace ECS {
    namespace System {

        SysMenu::SysMenu()
                : _userlogged(false), _userSignup(false), _pwdSignup(false), _userpwd(false), _selectedItemIndex(0),
                  _w(1280), _h(720) {
            if (!_font.loadFromFile("SIXTY.ttf")) {
                // handle error
            }
        }

        void SysMenu::update(WorldData &world) {
            Component::CompWindow *windowc = dynamic_cast<Component::CompWindow *>(world._systemEntity.getComponent(ECS::Component::WINDOW));
            if (!windowc || !windowc->window)
                return;

            sf::Event event;

            while (windowc->window->isOpen()) {
                if (!this->isUserLogged())
                    this->login(*windowc->window);
                else if (!this->isPwdCorrect())
                    this->pwd(*windowc->window);
                else {
                    while (windowc->window->pollEvent(event)) {
                        switch (event.type) {
                            case sf::Event::KeyReleased:
                                switch (event.key.code) {
                                    case sf::Keyboard::Up:
                                        this->MoveUp();
                                        break;
                                    case sf::Keyboard::Down:
                                        this->MoveDown();
                                        break;
                                    case sf::Keyboard::Return:
                                        switch (this->GetPressedItem()) {
                                            case 0:
                                                std::cout << "Play button has been pressed" << std::endl;
                                                break;
                                            case 1:
                                                std::cout << "Room button has been pressed" << std::endl;
                                                break;
                                            case 2:
                                                std::cout << "Option button has been pressed" << std::endl;
                                                break;
                                            case 3:
                                                windowc->window->close();
                                                break;
                                        }
                                        break;
                                }
                                break;
                            case sf::Event::Closed:
                                windowc->window->close();
                                break;
                        }
                        windowc->window->clear();
                        windowc->window->display();
                    }
                }
            }
        }

        void SysMenu::login(sf::RenderWindow &window) {
            sf::Event event;
            while (window.pollEvent(event) && !_userlogged) {
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode < 128) {
                        if (event.text.unicode == 13) {
                            _userlogged = true;
                        } else if (event.text.unicode == 8) {
                            if (_user.size() > 0)
                                _user.resize(_user.size() - 1);
                        } else
                            _user += static_cast<char>(event.text.unicode);
                    }
                }
            }
            _inputLogin[0].setFont(_font);
            _inputLogin[0].setFillColor(sf::Color::White);
            _inputLogin[0].setString("Login : " + _user);
            _inputLogin[0].setCharacterSize(35);
            _inputLogin[0].setPosition(sf::Vector2f(_w / 3, _h / 3));
            window.clear();
            window.draw(_inputLogin[0]);
            window.display();
        }

        void SysMenu::signUpLogin(sf::RenderWindow &window) {
            sf::Event event;
            while (window.pollEvent(event) && !_userSignup) {
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode < 128) {
                        if (event.text.unicode == 13) {
                            _userSignup = true;
                        } else if (event.text.unicode == 8) {
                            if (_user.size() > 0)
                                _user.resize(_user.size() - 1);
                        } else
                            _user += static_cast<char>(event.text.unicode);
                    }
                }
            }
            _signUp[0].setFont(_font);
            _signUp[0].setFillColor(sf::Color::White);
            _signUp[0].setString("Login : " + _user);
            _signUp[0].setCharacterSize(35);
            _signUp[0].setPosition(sf::Vector2f(_w / 3, _h / 3));
            window.clear();
            window.draw(_signUp[0]);
            window.display();
        }

        void SysMenu::pwd(sf::RenderWindow &window) {
            sf::Event event;
            while (window.pollEvent(event) && !_userpwd) {
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode < 128) {
                        if (event.text.unicode == 13) {
                            _userpwd = true;
                        } else if (event.text.unicode == 8) {
                            if (_pwd.size() > 0) {
                                _pwd.resize(_pwd.size() - 1);
                                _cryptedPwd.resize(_cryptedPwd.size() - 1);
                            }
                        } else {
                            _pwd += static_cast<char>(event.text.unicode);
                            _cryptedPwd += '*';
                        }
                    }
                }
            }
            _inputLogin[1].setFont(_font);
            _inputLogin[1].setFillColor(sf::Color::White);
            _inputLogin[1].setString("Login ok\n\nPassword : " + _cryptedPwd);
            _inputLogin[1].setCharacterSize(35);
            _inputLogin[1].setPosition(sf::Vector2f(_w / 3, _h / 3));
            window.clear();
            window.draw(_inputLogin[1]);
            window.display();
        }

        void SysMenu::pwdSignUp(sf::RenderWindow &window) {
            sf::Event event;
            while (window.pollEvent(event) && !_pwdSignup) {
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode < 128) {
                        if (event.text.unicode == 13) {
                            _pwdSignup = true;
                        } else if (event.text.unicode == 8) {
                            if (_pwd.size() > 0) {
                                _pwd.resize(_pwd.size() - 1);
                                _cryptedPwd.resize(_cryptedPwd.size() - 1);
                            }
                        } else {
                            _pwd += static_cast<char>(event.text.unicode);
                            _cryptedPwd += '*';
                        }
                    }
                }
            }
            _signUp[1].setFont(_font);
            _signUp[1].setFillColor(sf::Color::White);
            _signUp[1].setString("Login ok\n\nPassword : " + _cryptedPwd);
            _signUp[1].setCharacterSize(35);
            _signUp[1].setPosition(sf::Vector2f(_w / 3, _h / 3));
            window.clear();
            window.draw(_signUp[1]);
            window.display();
        }

        void SysMenu::menu_room() {
            _inputLogin[0].setFont(_font);
            _inputLogin[0].setFillColor(sf::Color::Green);
            _inputLogin[0].setString("Hello " + _user);
            _inputLogin[0].setCharacterSize(55);
            _inputLogin[0].setPosition(sf::Vector2f(_w / 2 - 150, _h - _h + 50));

            _menu[0].setFont(_font);
            _menu[0].setFillColor(sf::Color::Red);
            _menu[0].setString("Room");
            _menu[0].setCharacterSize(35);
            _menu[0].setPosition(sf::Vector2f(_w / 2 - 75, _h - _h + 200));

            _menu[1].setFont(_font);
            _menu[1].setFillColor(sf::Color::White);
            _menu[1].setString("Options");
            _menu[1].setCharacterSize(35);
            _menu[1].setPosition(sf::Vector2f(_w / 2 - 75, _h - _h + 250));

            _menu[2].setFont(_font);
            _menu[2].setFillColor(sf::Color::White);
            _menu[2].setString("Exit");
            _menu[2].setCharacterSize(35);
            _menu[2].setPosition(sf::Vector2f(_w / 2 - 75, _h - _h + 300));
        }

        void SysMenu::menu_signup() {
            _signUp[0].setFont(_font);
            _signUp[0].setFillColor(sf::Color::Red);
            _signUp[0].setString("Signup");
            _signUp[0].setCharacterSize(35);
            _signUp[0].setPosition(sf::Vector2f(_w / 2 - 75, _h - _h + 200));

            _signUp[1].setFont(_font);
            _signUp[1].setFillColor(sf::Color::White);
            _signUp[1].setString("Login");
            _signUp[1].setCharacterSize(35);
            _signUp[1].setPosition(sf::Vector2f(_w / 2 - 75, _h - _h + 250));
        }

        void SysMenu::drawRoomMenu(sf::RenderWindow &window) const {
            window.draw(_inputLogin[0]);
            for (int i = 0; i < NB_ITEMS; i++) {
                window.draw(_menu[i]);
            }
        }

        void SysMenu::drawSignMenu(sf::RenderWindow &window) const {
            for (int i = 0; i < NB_ITEMS; i++) {
                window.draw(_signUp[i]);
            }
        }

        void SysMenu::MoveUp() {
            if (_selectedItemIndex - 1 >= 0) {
                _menu[_selectedItemIndex].setFillColor(sf::Color::White);
                _selectedItemIndex--;
                _menu[_selectedItemIndex].setFillColor(sf::Color::Red);
            }
        }

        void SysMenu::MoveDown() {
            if (_selectedItemIndex + 1 < NB_ITEMS) {
                _menu[_selectedItemIndex].setFillColor(sf::Color::White);
                _selectedItemIndex++;
                _menu[_selectedItemIndex].setFillColor(sf::Color::Red);
            }
        }

        void SysMenu::MoveUpSign() {
            if (_selectedItemIndex - 1 >= 0) {
                _signUp[_selectedItemIndex].setFillColor(sf::Color::White);
                _selectedItemIndex--;
                _signUp[_selectedItemIndex].setFillColor(sf::Color::Red);
            }
        }

        void SysMenu::MoveDownSign() {
            if (_selectedItemIndex + 1 < NB_ITEMS) {
                _signUp[_selectedItemIndex].setFillColor(sf::Color::White);
                _selectedItemIndex++;
                _signUp[_selectedItemIndex].setFillColor(sf::Color::Red);
            }
        }
    }
}