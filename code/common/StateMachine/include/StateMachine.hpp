/**
 * @file StateMachine.hpp
 * @author Tookie
 * @brief Implemention of a state machine
 */

#pragma once

#include <memory>
#include "State.hpp"

/**
 * namespace for state machin
 */
namespace state_machine
{
    /**
     * representation of a state machine
     * @tparam Edge use to create and link states
     */
    template<typename Edge>
    class StateMachine
    {
    private:
        using StateT = State<Edge>;

    public:
        /**
         * Constructor of StateMachine
         */
        StateMachine() :
            _initialState("")
        {};

        StateMachine(const StateMachine &) = delete;

        StateMachine &operator=(const StateMachine &) = delete;

        /**
         * Constructor of StateMachine
         * @param initialState name of the initial state
         */
        StateMachine(const std::string &initialState) :
            _initialState(initialState)
        {};

        /**
         * Constructor of StateMachine
         * @param initialState initial state
         */
        StateMachine(std::shared_ptr<StateT> initialState) :
            _initialState(initialState->getName()), _states{{_initialState, initialState}}
        {
        };

        /**
         * Constructor of StateMachine
         */
        ~StateMachine()
        {};

        /**
         * use to add one state to the state machine
         * @param state
         */
        void addState(std::shared_ptr<StateT> state)
        {
            if (_states.size() == 0 && _initialState.empty())
                _initialState = state->getName();
            _states[state->getName()] = state;
        };

        /**
         * setter for initial state
         * @param nameState name of the initial state
         * @throw out of range exception if the name isn't in the states
         */
        void setInitialState(const std::string &nameState)
        {
            if (_states.find(nameState) != _states.end())
                _initialState = nameState;
            else
                throw std::out_of_range(nameState + " does not match with any state");
        }

        /**
         * setter for initial state
         * @param state initial state
         */
        void setInitialState(const std::shared_ptr<StateT> state)
        {
            if (_states.find(state->getName() == _states.end()))
                addState(state);
            _initialState = state->getName();
        }

        /**
         * getter for initial state
         * @return name of the initial state
         */
        const std::string &getInitialState() const
        {
            return _initialState;
        }

        /**
         * return the state who has the name given as parameter
         * @param name name of the state
         * @return shared ptr to the state
         * @throw out of range exception if the name isn't in the states map
         */
        const std::shared_ptr<StateT> operator[](const std::string &name)
        {
            if (_states.find(name) == _states.end())
                throw std::out_of_range(name + " does not match with any state");
            return _states.find(name)->second;
        }

        /**
         * clear the state machine
         */
        void clear()
        {
            _states.clear();
            _initialState.clear();
        }

    private:
        /**
         * contains all states include on state machine with their name as key
         */
        std::map<std::string, std::shared_ptr<StateT> > _states;

        /**
         * the name of the initial state of the state machine
         */
        std::string _initialState;


    };
}