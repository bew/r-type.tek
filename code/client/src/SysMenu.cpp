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
      _reactions["s_menu"] = &SysMenu::menuRoomChoose;
      _reactions["s_room_wait"] = &SysMenu::menuGameLaunch;
      _reactions["s_game"] = &SysMenu::running;
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
      sf::Text connect;
      sf::Text create;
      sf::Text loginDesc;
      sf::Text passwordDesc;
      
      if (!windowc || !assetc || !loginc || !networkc)
	return ;

      if (index % 4 == 0) {
	loginDesc.setFillColor(sf::Color::Green);
	if (up || down)
	  text_input = loginc->login;
	else
	  loginc->login = text_input;
      }

      else if (index % 4 == 1) {
	passwordDesc.setFillColor(sf::Color::Green);
        if (up || down)
          text_input = loginc->password;
        else
          loginc->password = text_input;
      }

      else if (index % 4 == 2) {
	connect.setFillColor(sf::Color::Green);
        if (validate) {
	  networkc->_clientTCP.addMessage(protocol::client::login(loginc->login, loginc->password).getBufferString() + network::magic);
	  stateMachine->_nextState = "s_menu";
	}
      }

      else if (index % 4 == 3) {
        create.setFillColor(sf::Color::Green);
        if (validate) {
          networkc->_clientTCP.addMessage(protocol::client::signUp(loginc->login, loginc->password).getBufferString() + network::magic);
          stateMachine->_nextState = "s_auth";
        }
      }
        
      try {
	connect.setFont(assetc->store.getFont("gui").getLowLevelFont());
	create.setFont(assetc->store.getFont("gui").getLowLevelFont());
	loginDesc.setFont(assetc->store.getFont("gui").getLowLevelFont());
	passwordDesc.setFont(assetc->store.getFont("gui").getLowLevelFont());
	connect.setString(assetc->store.getText("loginin").getText());
	create.setString(assetc->store.getText("subscribe").getText());
	loginDesc.setString(assetc->store.getText("login").getText() + loginc->login);
        passwordDesc.setString(assetc->store.getText("password").getText() + std::string(loginc->password.size(), '*'));
        loginDesc.setPosition(500, 200);
        passwordDesc.setPosition(500, 300);
	connect.setPosition(500, 400);
	create.setPosition(500, 500);
	windowc->window->draw(connect);
	windowc->window->draw(create);
	windowc->window->draw(loginDesc);
        windowc->window->draw(passwordDesc);
      } catch (const graphic::AssetException &e) {
	logs::getLogger()[logs::ASSET] << e.what() << std::endl;
      }
    }

    void SysMenu::menuRoomChoose(ECS::WorldData &world) {
      Component::CompWindow* windowc = dynamic_cast<Component::CompWindow *>(world._systemEntity.getComponent(ECS::Component::WINDOW));
      Component::CompAsset* assetc = dynamic_cast<Component::CompAsset *>(world._systemEntity.getComponent(ECS::Component::STANDARD_ASSET));
      Component::CompLogin* loginc = dynamic_cast<Component::CompLogin *>(world._systemEntity.getComponent(ECS::Component::LOGIN));
      Component::CompNetworkClient* networkc = dynamic_cast<Component::CompNetworkClient *>(world._systemEntity.getComponent(ECS::Component::NETWORK_CLIENT));
      Component::CompStateMachine* stateMachine = dynamic_cast<Component::CompStateMachine *>(world._systemEntity.getComponent(ECS::Component::STATE_MACHINE));
      sf::Text join;
      sf::Text password;
      sf::Text go;

      if (!windowc || !assetc || !loginc || !networkc)
	return ;
      
      if (index % 3 == 2) {
        join.setFillColor(sf::Color::Green);
	if (up || down)
          text_input = loginc->room;
        else
          loginc->room = text_input;
      }

      else if (index % 3 == 1) {
        password.setFillColor(sf::Color::Green);
	if (up || down)
          text_input = loginc->roomPassword;
        else
          loginc->roomPassword = text_input;
      }
      else if (index % 3 == 0) {
	go.setFillColor(sf::Color::Green);
	if (validate) {
	  networkc->_clientTCP.addMessage(protocol::client::roomJoin(loginc->room, loginc->roomPassword).getBufferString() + network::magic);
	  stateMachine->_nextState = "s_room_wait";
	}
      }

      try {
	password.setFont(assetc->store.getFont("gui").getLowLevelFont());
	join.setFont(assetc->store.getFont("gui").getLowLevelFont());
	go.setFont(assetc->store.getFont("gui").getLowLevelFont());
	go.setString(assetc->store.getText("roomvalidate").getText());
        go.setPosition(500, 500);
	password.setString(assetc->store.getText("roompassword").getText() + std::string(loginc->roomPassword.size(), '*'));
	password.setPosition(500, 300);
        join.setString(assetc->store.getText("joinroom").getText() + loginc->room);
	join.setPosition(500, 400);
        windowc->window->draw(join);
	windowc->window->draw(password);
        windowc->window->draw(go);
      } catch (const graphic::AssetException &e) {
        logs::getLogger()[logs::ASSET] << e.what() << std::endl;
      }
    }

    void SysMenu::menuGameLaunch(ECS::WorldData &world) {
      Component::CompWindow* windowc = dynamic_cast<Component::CompWindow *>(world._systemEntity.getComponent(ECS::Component::WINDOW));
      Component::CompAsset* assetc = dynamic_cast<Component::CompAsset *>(world._systemEntity.getComponent(ECS::Component::STANDARD_ASSET));
      Component::CompLogin* loginc = dynamic_cast<Component::CompLogin *>(world._systemEntity.getComponent(ECS::Component::LOGIN));
      Component::CompNetworkClient* networkc = dynamic_cast<Component::CompNetworkClient *>(world._systemEntity.getComponent(ECS::Component::NETWORK_CLIENT));
      Component::CompStateMachine* stateMachine = dynamic_cast<Component::CompStateMachine *>(world._systemEntity.getComponent(ECS::Component::STATE_MACHINE));

      if (!windowc || !assetc || !loginc || !networkc)
        return ;

      try {
	loginc->isOwner = networkc->_lastReceived["data"]["data"]["players"].getValueDocument().elementsCount() == 1;
	for (auto i :  networkc->_lastReceived["data"]["data"]["generators"].getValueDocument().getKeys())
	  loginc->generators.push_back(networkc->_lastReceived["data"]["data"]["generators"][i].getValueString());
      }
      catch (const bson::BsonException &e) {
	logs::getLogger()[logs::ERRORS] << "Cannot check for room ownership : '" << e.what() << "'" << std::endl;
	return ;
      }

      if (!loginc->isOwner) {
	sf::Text wait;

	try {
	  wait.setFont(assetc->store.getFont("gui").getLowLevelFont());
	  wait.setString(assetc->store.getText("waitforgamestart").getText());
	  wait.setPosition(500, 360);
	  windowc->window->draw(wait);
	} catch (const graphic::AssetException &e) {
	  logs::getLogger()[logs::ASSET] << e.what() << std::endl;
	}
      }

      if (loginc->isOwner) {
        sf::Text wait;

	if (loginc->generators.size() == 0) {
	  try {
            wait.setFont(assetc->store.getFont("gui").getLowLevelFont());
            wait.setString(assetc->store.getText("nogenerator").getText());
            wait.setPosition(500, 360);
            windowc->window->draw(wait);
          } catch (const graphic::AssetException &e) {
            logs::getLogger()[logs::ASSET] << e.what() << std::endl;
          }
	}
	else {

	  if (validate) {
	    networkc->_clientTCP.addMessage(protocol::client::gameStart(loginc->generators[index % loginc->generators.size()]).getBufferString() + network::magic);
	    stateMachine->_nextState = "s_room_wait";
	  }
	  
	  try {
	    wait.setFont(assetc->store.getFont("gui").getLowLevelFont());
	    wait.setString(assetc->store.getText("choosegenerator").getText() + loginc->generators[index % loginc->generators.size()]);
	    wait.setPosition(500, 360);
	    windowc->window->draw(wait);
	  } catch (const graphic::AssetException &e) {
	    logs::getLogger()[logs::ASSET] << e.what() << std::endl;
	  }
	}
      }
    }


    void SysMenu::running(ECS::WorldData &world) { 
      Component::CompAsset *assetc = dynamic_cast<Component::CompAsset*>(world._systemEntity.getComponent(ECS::Component::STANDARD_ASSET));
      Component::CompWindow *windowc = dynamic_cast<Component::CompWindow*>(world._systemEntity.getComponent(ECS::Component::WINDOW));
      Component::CompScore *scorec = dynamic_cast<Component::CompScore*>(world._systemEntity.getComponent(ECS::Component::SCORE));
      Component::CompNetworkClient* networkc = dynamic_cast<Component::CompNetworkClient *>(world._systemEntity.getComponent(ECS::Component::NETWORK_CLIENT));

      if (networkc && !networkc->_clientUDP) {
	try {
	  networkc->_clientUDP = new network::ClientUDP(networkc->_address, static_cast<short>(networkc->_lastReceived["data"]["port"].getValueInt32()));
	  networkc->_serverToken = networkc->_lastReceived["data"]["serverToken"].getValueString();
	  networkc->_clientToken = networkc->_lastReceived["data"]["clientToken"].getValueString();
	}
	catch (const bson::BsonException &e) {
	  logs::getLogger()[logs::ERRORS] << "Cannot create udp connection : '" << e.what() << "'" << std::endl;
	  return ;
	}
	catch (const network::SocketException &e) {
          logs::getLogger()[logs::ERRORS] << "Cannot create udp connection : '" << e.what() << "'" << std::endl;
          return ;
	}
      }

      
      if (windowc && windowc->window && assetc && scorec) {
        try {
          std::string scoreString = assetc->store.getText("scoregui").getText() + std::to_string(scorec->score);

          for (ECS::Entity::Entity *entity : world._gameEntities) {
            if (entity->getId() >= 1 && entity->getId() <= 4) {
              Component::CompLife *lifec = dynamic_cast<Component::CompLife*>(entity->getComponent(ECS::Component::LIFE));
              if (lifec)
                scoreString += "   P" + std::to_string(entity->getId()) + assetc->store.getText("lifegui").getText() + std::to_string(lifec->getCurrentLife());
            }
          }
          sf::Text score(scoreString, assetc->store.getFont("gui").getLowLevelFont());
          score.setPosition(20.0, 20.0);
          windowc->window->draw(score);
        } catch (const graphic::AssetException &e) {
          logs::getLogger()[logs::ASSET] << e.what() << std::endl;
        }
      }
    }    
  }
}
