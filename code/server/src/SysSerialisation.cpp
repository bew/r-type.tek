/**
 * @file SysSerialisation.cpp
 * @author Nekhot
 * @brief Impelmentation of system udp packet.
 */

#include "SysSerialisation.hh"

namespace ECS {
  namespace System {

    void SysSerialisation::serialize(WorldData &world, Entity::Entity *entity) {
      Component::CompNetworkServer *serverc = dynamic_cast<Component::CompNetworkServer*>(world._systemEntity.getComponent(ECS::Component::NETWORK_SERVER));

      bson::Document components;
      if (serverc) {
	for (auto componentEntry : entity->getComponents()) {
	  if (componentEntry.second->hasFlag(Component::SERVER_SERIALIZABLE_MASK)) {
	    try {
	      if (componentEntry.second->getType() == Component::CONTROLLER) {
		if (entity->getId() >= 1 && entity->getId() <= 4 && entity->getId() <= serverc->_server.getConnections().size()) {
		  bson::Document controller;
		  controller <<  Component::CONTROLLER << componentEntry.second->serialize();
		  serverc->_server.addMessage
		    (serverc->_server.getConnections()[entity->getId() - 1],
		     protocol::client::entityUpdate(serverc->_serverToken, entity->getId(), controller).getBufferString() + network::magic);
		}
	      }
	      else
		components << componentEntry.second->getType() << componentEntry.second->serialize();
	    }
	    catch (const Component::ComponentFlagException &e) {
	      logs::getLogger()[logs::ERRORS] << e.what() << std::endl;
	    }
	  }
	}
	for (auto connected : serverc->_server.getConnections()) {
	  serverc->_server.addMessage(connected, protocol::client::entityUpdate(serverc->_serverToken, entity->getId(), components).getBufferString() + network::magic);
	}
	serverc->_server.update();
      }
    }
    
    void SysSerialisation::update(WorldData &world) {
      unserialize(world);
      serialize(world, &world._systemEntity);
      for (Entity::Entity *entity : world._gameEntities)
	serialize(world, entity);
    }

    void SysSerialisation::unserialize(WorldData &world) {

      Component::CompNetworkServer *serverc = dynamic_cast<Component::CompNetworkServer*>(world._systemEntity.getComponent(ECS::Component::NETWORK_SERVER));

      if (serverc) {
	try {
	  serverc->_server.update();
	}
	catch (const network::SocketException &e) {
	  logs::getLogger()[logs::ERRORS] << e.what() << std::endl;
	}
	std::string message;
	for (auto connected : serverc->_server.getConnections()) {
	  while (!(message = serverc->_server.getMessage(connected)).empty()) {
	    try {
	      bson::Document document(message);
	      if (!protocol::server::checkEntityUpdate(document))
		logs::getLogger()[logs::ERRORS] << "Invalid packet" << std::endl;
	      else if (std::find(serverc->_clientTokens.begin(), serverc->_clientTokens.end(), document["data"]["token"].getValueString()) == serverc->_clientTokens.end())
		logs::getLogger()[logs::ERRORS] << "Invalid client token" << std::endl;
	      else {
		Entity::Entity *entity = world.getEntityById(document["data"]["entity_id"].getValueInt64());
		if (!entity) {
		  logs::getLogger()[logs::ERRORS] << "Client tried to create new entity with id " << document["data"]["entity_id"].getValueInt64() << std::endl;
		}
		else {
		  const bson::Document &components = document["data"]["components"].getValueDocument();
		  for (const std::string &key : components.getKeys()) {
		    Component::AComponent *component = entity->getComponent(key);
		    if (component) {
		      try {
			component->deserialize(components[key].getValueDocument());
		      }
		      catch (const Component::ComponentFlagException &e) {
			logs::getLogger()[logs::ERRORS] << e.what() << std::endl;
		      }
		    }
		    else {
		      logs::getLogger()[logs::ERRORS] << "Client tried to create new component '" << key << "'" << std::endl;
		    }
		  }
		}	      
	      }
	    }
	    catch (const bson::BsonException &e) {
	      logs::getLogger()[logs::ERRORS] << e.what() << std::endl;
	    }
	  }
	}
      }
    }
  }
}
