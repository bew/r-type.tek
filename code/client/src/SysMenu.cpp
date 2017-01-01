//
// Created by heuse on 23/12/2016.
//

#include "SysMenu.hh"

namespace ECS {
  namespace System {

    SysMenu::SysMenu() :
      index(123456),
      up(false),
      down(false),
      text_input(""),
      validate(false)
    {
      _reactions["s_auth"] = &SysMenu::menuSignup;
    }

    void SysMenu::update(WorldData &world) {
      Component::CompWindow* windowc = dynamic_cast<Component::CompWindow *>(world._systemEntity.getComponent(ECS::Component::WINDOW));
      Component::CompStateMachine* stateMachine = dynamic_cast<Component::CompStateMachine *>(world._systemEntity.getComponent(ECS::Component::STATE_MACHINE));
      Component::CompNetworkClient* network = dynamic_cast<Component::CompNetworkClient *>(world._systemEntity.getComponent(ECS::Component::NETWORK_CLIENT));
      Component::CompTick *tickc = dynamic_cast<Component::CompTick *>(world._systemEntity.getComponent(ECS::Component::TICK));

      if (!windowc || !windowc->window || !stateMachine || !network)
        return ;
            
      sf::Event event;
      validate = false;
      up = false;
      down = false;
      
      while (windowc->window->pollEvent(event)) {
	switch (event.type) {
	case sf::Event::TextEntered:
	  if (event.text.unicode == 8 && text_input.size() > 0)
	    text_input.pop_back();
	  else if (event.text.unicode >= 48 && event.text.unicode <= 125)
	    text_input += static_cast<char>(event.text.unicode);
	  break;
	case sf::Event::KeyReleased:
	  switch (event.key.code) {
	  case sf::Keyboard::Escape:
	    windowc->window->close();
	    if (tickc)
	      tickc->kill = true;
	    break;
	  case sf::Keyboard::Up:
	    --index;
	    up = true;
	    text_input = "";
	    break;
	  case sf::Keyboard::Down:
	    ++index;
	    down = true;
	     text_input = "";
	    break;
	  case sf::Keyboard::Return:
	    validate = true;
	     text_input = "";
	    break;
	  default:
	    break;
	  }
	  break;
	case sf::Event::Closed:
	  windowc->window->close();
	  if (tickc)
	    tickc->kill = true;
	  break;
	default:
	  break;
	}
      }

      try {
	Menu currentMenu = _reactions.at(stateMachine->_currentState);
	(this->*currentMenu)(world);
      }
      catch (const std::out_of_range &e) {
	logs::getLogger()[logs::ERRORS] << "Unhandled state '" << stateMachine->_currentState << "'" << std::endl;
      }
      
      windowc->window->display();
      windowc->window->clear();
    }
    
    void SysMenu::menuSignup(ECS::WorldData &world) {
      Component::CompWindow* windowc = dynamic_cast<Component::CompWindow *>(world._systemEntity.getComponent(ECS::Component::WINDOW));
      Component::CompAsset* assetc = dynamic_cast<Component::CompAsset *>(world._systemEntity.getComponent(ECS::Component::STANDARD_ASSET));
      Component::CompLogin* loginc = dynamic_cast<Component::CompLogin *>(world._systemEntity.getComponent(ECS::Component::LOGIN));
      Component::CompNetworkClient* networkc = dynamic_cast<Component::CompNetworkClient *>(world._systemEntity.getComponent(ECS::Component::NETWORK_CLIENT));
      Component::CompStateMachine* stateMachine = dynamic_cast<Component::CompStateMachine *>(world._systemEntity.getComponent(ECS::Component::STATE_MACHINE));
      sf::Text title;
      sf::Text loginDesc;
      sf::Text passwordDesc;
      
      if (!windowc || !assetc || !loginc || !networkc)
	return ;

      title.setFont(assetc->store.getFont("gui").getLowLevelFont());
      loginDesc.setFont(assetc->store.getFont("gui").getLowLevelFont());
      passwordDesc.setFont(assetc->store.getFont("gui").getLowLevelFont());
      
      if (index % 3 == 0) {
	loginDesc.setFillColor(sf::Color::Green);
	if (up || down)
	  text_input = loginc->login;
	else
	  loginc->login = text_input;
      }

      if (index % 3 == 1) {
	passwordDesc.setFillColor(sf::Color::Green);
        if (up || down)
          text_input = loginc->password;
        else
          loginc->password = text_input;
      }

      if (index % 3 == 2) {
	title.setFillColor(sf::Color::Green);
        if (validate) {
	  networkc->_clientTCP.addMessage(protocol::client::login(loginc->login, loginc->password).getBufferString() + network::magic);
	  stateMachine->_nextState = "s_menu";
	}
      }
        
      try {
	title.setString(assetc->store.getText("loginin").getText());
	loginDesc.setString(assetc->store.getText("login").getText() + loginc->login);
        passwordDesc.setString(assetc->store.getText("password").getText() + loginc->password);
        loginDesc.setPosition(500, 200);
        passwordDesc.setPosition(500, 300);
	title.setPosition(500, 400);
	windowc->window->draw(title);
	windowc->window->draw(loginDesc);
        windowc->window->draw(passwordDesc);
      } catch (const graphic::AssetException &e) {
	logs::getLogger()[logs::ASSET] << e.what() << std::endl;
      }
    }
  }
}
