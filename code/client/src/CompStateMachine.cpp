/**
 * @file CompStateMachine.cpp
 * @author Tookie.
 * @brief component use to manipulate multiple state.
 */

#include "CompStateMachine.hh"

namespace ECS
{
    namespace Component
    {
        CompStateMachine::CompStateMachine() :
	  AComponent(),
	  _sm(),
	  _currentState("")
        {
            std::shared_ptr<state_machine::State<std::string>> sAuth = std::make_shared<state_machine::State<std::string>>("s_auth");
            std::shared_ptr<state_machine::State<std::string>> sMenu = std::make_shared<state_machine::State<std::string>>("s_menu");
            std::shared_ptr<state_machine::State<std::string>> sRoom = std::make_shared<state_machine::State<std::string>>("s_room_wait");
            std::shared_ptr<state_machine::State<std::string>> sGame = std::make_shared<state_machine::State<std::string>>("s_game");

            sAuth->addLink("login", sMenu->getName());
            sAuth->addLink("signup", sAuth->getName());

            sMenu->addLink("roomJoin", sRoom->getName());
            sMenu->addLink("logout", sAuth->getName());

            sRoom->addLink("roomKick", sMenu->getName());
            sRoom->addLink("gameStart", sGame->getName());
            sRoom->addLink("RoomLeave", sMenu->getName());

            sGame->addLink("gameLeave", sMenu->getName());
            sGame->addLink("logout", sAuth->getName());

            _sm.addState(sAuth);
            _sm.addState(sMenu);
            _sm.addState(sRoom);
            _sm.addState(sGame);

            _currentState = sAuth->getName();
        }

        CompStateMachine::CompStateMachine(const std::string &initialStateName)
            : AComponent(),
              _sm(initialStateName), _currentState(initialStateName)
        {}

        CompStateMachine::CompStateMachine(std::shared_ptr<state_machine::State<std::string> > initialState)
            : AComponent(),
              _sm(initialState), _currentState(initialState->getName())
        {}

        CompStateMachine::~CompStateMachine()
        {}

        const std::string &CompStateMachine::getType() const
        {
            return Component::STATE_MACHINE;
        }
    }
}
