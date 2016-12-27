/**
 * @file ClientCommandsState.cpp
 * @author Benoit de Chezelles
 * @brief Implementation of the client's commands state machine
 */

#include "ClientCommandsState.hpp"

ClientCommandsState::ClientCommandsState() :
  _sm()
{
  initStateMachine();
  _currentState = _sm[_sm.getInitialState()];
  _previousState = _currentState;
}

ClientCommandsState::~ClientCommandsState()
{}

bool ClientCommandsState::gotoNextStateVia(std::string const & action)
{
  if (!_currentState->has(action))
    return false;

  _previousState = _currentState;
  _currentState = _sm[_previousState->getLink(action)];
  return true;
}

void ClientCommandsState::revertToPreviousState()
{
  if (_currentState != _previousState)
    _currentState = _previousState;
}

std::shared_ptr<state_machine::State<std::string>> ClientCommandsState::getCurrentState() const
{
  return _currentState;
}

/**
 * Different states of the Player, with transitionnal commands
 *
 *           +-------+
 * This is a | State |
 *           +-------+
 *
 * All arrows start on the bottom of
 * a State
 *
 *               +----------+
 *             __| S_NoAuth |____
 *            /  +----------+    \
 *     SignUp \_______/|         |
 *                     |         |
 *                   Login       |
 *                     |         |
 *                +--------+     | Logout
 *            ____| S_Lost |     |
 *           /    +--------+     *
 *           |         |  \_____/|
 *           |         |         |
 *           |      RoomJoin     |
 *           |         |         |
 * RoomLeave |    +---------+    |
 * RoomKick  |   _| S_Lobby |    |
 *           |  / +---------+    *
 *           \__|_____/|  \_____/|
 *              |      |         |
 *              |  GameStart     |
 *              |      |         |
 *    GameLeave | +--------+     |
 *              | | S_Game |     |
 *              | +--------+     |
 *              \__/      \______/
 *
 */
void ClientCommandsState::initStateMachine()
{
  using StateT = state_machine::State<std::string>;

  auto no_auth = std::make_shared<StateT>("S_NoAuth");
  auto lost = std::make_shared<StateT>("S_Lost");
  auto lobby = std::make_shared<StateT>("S_Lobby");
  auto game = std::make_shared<StateT>("S_Game");

  _sm.setInitialState(no_auth);
  _sm.addState(lost);
  _sm.addState(lobby);
  _sm.addState(game);

  no_auth->addLink("Login", *lost);
  no_auth->addLink("SignUp", *no_auth);

  lost->addLink("RoomJoin", *lobby);
  lost->addLink("Logout", *no_auth);

  lobby->addLink("RoomLeave", *lost);
  lobby->addLink("RoomKick", *lost);
  lobby->addLink("GameStart", *game);
  lobby->addLink("Logout", *no_auth);

  game->addLink("GameLeave", *lobby);
  game->addLink("Logout", *no_auth);
}
