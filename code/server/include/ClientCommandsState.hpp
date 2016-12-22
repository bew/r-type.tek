/**
 * @file ClientCommandsState.hpp
 * @author Benoit de Chezelles
 * @brief Class the client's commands state machine
 */

#pragma once

#include "StateMachine.hpp"

/**
 * Represent a Navigable State Machine for client's commands
 */
class ClientCommandsState
{
public:
  /**
   * Ctor
   */
  ClientCommandsState();

  /**
   * Dtor
   */
  ~ClientCommandsState();

  ClientCommandsState(ClientCommandsState const & other) = delete;
  ClientCommandsState & operator=(ClientCommandsState const & other) = delete;

public:
  /**
   * Change the current state through the transition 'action'
   *
   * @param action The transition name
   * @return true if the a state can be reached, else false
   */
  bool gotoNextStateVia(std::string const & action);

  /**
   * Revert the current state to it's last state
   *
   * Does nothing if the two are equal
   */
  void revertToPreviousState();

private:
  /**
   * Initialize the internal state machine
   */
  void initStateMachine();

protected:
  /**
   * Store the state machine
   */
  state_machine::StateMachine<std::string> _sm;

  /**
   * Store the current state
   */
  std::shared_ptr<state_machine::State<std::string>> _currentState;

  /**
   * Store the previous known state
   *
   * Can be equal to _currentState if there is no previous state, or if a
   * revertToPreviousState has been done.
   */
  std::shared_ptr<state_machine::State<std::string>> _previousState;
};
