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
        CompStateMachine::CompStateMachine() : AComponent(), _sm(),
                                               _currentState("")
        {}

        CompStateMachine::CompStateMachine(const std::string &initialStateName)
            : AComponent(),
              _sm(initialStateName), _currentState("initialState")
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