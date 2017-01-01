/**
 * @file SysStateMachine.cpp
 * @author Tookie
 * @brief implementation of System for State Machine.
 */

#include "ECS/ECSLogLevel.hh"
#include "SysStateMachine.hh"
#include "Protocol/Server.hh"
#include "Network/SocketException.hh"

namespace ECS
{
  namespace System
  {
    void SysStateMachine::processMessage(const bson::Document &doc,
					 Component::CompStateMachine &stateMachine,
					 Component::CompNetworkClient &network) {
      
      if (network.isValidActionTcp(doc["header"]["action"].getValueString())) {
	const std::string &action = doc["header"]["action"].getValueString();
	if (stateMachine._sm[stateMachine._currentState]->has(action)) {
	  stateMachine._currentState = stateMachine._sm[stateMachine._currentState]->getLink(action);
	  network._lastReceived = doc;
	  network._clientTCP.addMessage(protocol::answers::ok(doc["header"]["timestamp"].getValueInt64(),
							      bson::Document()).getBufferString() +
					network::magic);
	}
	else {
	  network._clientTCP.addMessage(protocol::answers::unauthorized(doc["header"]["timestamp"].getValueInt64()).getBufferString() +
					network::magic);
	}
      }
      else if (doc["header"]["action"].getValueString() != "Answer")
	network._clientTCP.addMessage(protocol::answers::notFound(doc["header"]["timestamp"].getValueInt64()).getBufferString() +
				      network::magic);
      else if (protocol::answers::checkAnswer(doc)
	       && doc["data"]["code"].getValueInt32() == 200
	       && !stateMachine._nextState.empty()
	       && stateMachine._sm[stateMachine._currentState]->canAccessState(stateMachine._nextState)) {
	stateMachine._currentState = stateMachine._nextState;
	stateMachine._nextState.clear();
	network._lastReceived = doc;
      }
      else {
	network._lastReceived = doc;
      }
    }

    void SysStateMachine::update(ECS::WorldData &world)
    {
      Component::CompNetworkClient *network = dynamic_cast<Component::CompNetworkClient *>(world._systemEntity.getComponent(Component::NETWORK_CLIENT));
      Component::CompStateMachine *stateMachine = dynamic_cast<Component::CompStateMachine *> (world._systemEntity.getComponent(Component::STATE_MACHINE));

      if (network && stateMachine) {
	network->_clientTCP.update();
	if (!network->_clientTCP.hasMessage())
	  return;
	try {
	  bson::Document doc;
	  try {
	    doc = bson::Document(network->_clientTCP.getMessage());
	  }
	  catch (bson::BsonException &bsonError) {
	    network->_clientTCP.addMessage(
					   protocol::answers::badRequest(-1).getBufferString() + network::magic);
	    if (logs::getLogger().isRegister(logs::ERRORS))
	      logs::getLogger()[logs::ERRORS] << bsonError.what() << std::endl;
	    else
	      std::cerr << bsonError.what() << std::endl;
	    return;
	  }
	  if (protocol::checkMessage(doc))
	    processMessage(doc, *stateMachine, *network);
	  else{
	    if (doc.hasKey("header") && doc["header"].getValueType() == bson::DOCUMENT &&
		protocol::checkTimestamp(doc["header"].getValueDocument()))
	      network->_clientTCP.addMessage(
					     protocol::answers::badRequest(
									   doc["header"]["timestamp"].getValueInt64()).getBufferString() +
					     network::magic);
	    else
	      network->_clientTCP.addMessage(
					     protocol::answers::badRequest(-1).getBufferString() +
					     network::magic);
	  }
	}
	catch (network::SocketException &socketError){
	  if (logs::getLogger().isRegister(logs::ERRORS))
	    logs::getLogger()[logs::ERRORS] << socketError.what() << std::endl;
	  else
	    std::cerr << socketError.what() << std::endl;
	  return;
	}
	catch (bson::BsonException &bsonError){
	  network->_clientTCP.addMessage(
					 protocol::answers::internalServerError(-1).getBufferString() + network::magic);
	  if (logs::getLogger().isRegister(logs::ERRORS))
	    logs::getLogger()[logs::ERRORS] << bsonError.what() << std::endl;
	  else
	    std::cerr << bsonError.what() << std::endl;
	}
	network->_clientTCP.update();
      }
    }
  }
}
