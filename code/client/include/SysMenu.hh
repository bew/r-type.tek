/**
 * @file SysMenu.hh
 * @author Heuse.
 * @brief Header of System for Menu.
 */

#pragma once

#include "ECS/World.hh"
#include "ECS/Entity.hh"
#include "ECS/ISystem.hh"
#include "Graphic/SpriteAsset.hh"
#include "CompAsset.hh"
#include "CompWindow.hh"
#include "ECS/CompSprite.hh"
#include "ECS/CompMovement.hh"
#include "Logs/Logger.hh"
#include "ECS/AssetLogLevel.hh"
#include "ECS/CompTick.hh"
#include "Graphic/SpriteAsset.hh"
#include "Graphic/AnimatedSpriteAsset.hh"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics.hpp"
#include "SysWindow.hh"
#include <iostream>

#define NB_ITEMS 3

namespace ECS {
    namespace System {

        /**
         * System for sprite
         */
        class SysMenu : public ISystem {
        public:

            /**
             * Update method
             *
             * @param world All the data about the world
             */
            SysMenu();
            virtual void update(ECS::WorldData &world);
            void drawRoomMenu(sf::RenderWindow &window);
            void drawSignMenu(sf::RenderWindow &window);
            void login(sf::RenderWindow &window);
            void signUpLogin(sf::RenderWindow &window);
            void pwd(sf::RenderWindow &window);
            void pwdSignUp(sf::RenderWindow &window);
            void menu_signup();
            void menu_room();
            void draw_menu();
            void MoveUp();
            void MoveUpSign();
            void MoveDown();
            void MoveDownSign();
            int GetPressedItem() const {return _selectedItemIndex;}
            bool isUserLogged() const {return _userlogged;}
            bool isPwdCorrect() const {return _userpwd;}
            const std::string & getCryptedPwd() const {return _cryptedPwd;}
            const std::string & getLogin() const {return _user;}

        private:
            float _w;
            float _h;
            bool _userlogged;
            bool _userpwd;
            bool _userSignup;
            bool _pwdSignup;
            std::string _cryptedPwd;
            std::string _user;
            std::string _pwd;
            int _selectedItemIndex;
            sf::Font _font;
            sf::Text _menu[NB_ITEMS];
            sf::Text _inputLogin[2];
            sf::Text _signUp[2];
        };
    }
}
