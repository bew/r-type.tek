/**
 * @file CompStateMachine.hh
 * @author Tookie.
 * @brief component use to manipulate multiple state.
 */

#pragma once

#include <string>
#include "AComponent.hh"
#include "StateMachine/StateMachine.hpp"

/**
 * Namespace of ECS.
 */
namespace ECS
{
    /**
     * Namespace of components.
     */
    namespace Component
    {
        /**
         * Component type id.
         */
        static const std::string STATE_MACHINE = "state machine";

        /**
         * representation of a component state machine
         */
        class CompStateMachine: public AComponent
        {
        public:
            /**
             * Default constructor of component state machine
             */
            CompStateMachine();

            /**
             * Constructor of component state machine
             * @param initialStateName name of the initiale state
             */
            CompStateMachine(const std::string &initialStateName);

            /**
             * Constructor of componenet state machine
             * @param initialState initial state
             */
            CompStateMachine(std::shared_ptr<state_machine::State<std::string> > initialState);

            /**
             * Destructor of CompStateMachine
             */
            ~CompStateMachine();

            /**
             * get the type of component
             * @return string that represents his type
             */
            virtual const std::string &getType() const;

            /**
             * Representation of a state machine
             */
            state_machine::StateMachine<std::string> _sm;

            /**
             * Contains the name of the current state
             */
             std::string _currentState;
        };

    }

}