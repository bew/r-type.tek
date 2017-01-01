/**
 * @file SysSerialisation.cpp
 * @author Nekhot
 * @brief Impelmentation of system udp packet.
 */

#include "SysSerialisation.hh"

namespace ECS {
  namespace System {

    std::unordered_map<std::string, std::function<Component::AComponent*(const bson::Document &)>> SysSerialisation::builders;

    void SysSerialisation::serialize(WorldData &world, Entity::Entity *entity) {
      Component::CompNetworkClient *clientc = dynamic_cast<Component::CompNetworkClient*>(world._systemEntity.getComponent(ECS::Component::NETWORK_CLIENT));

      bson::Document components;
      if (clientc && clientc->_clientUDP) {
	for (auto componentEntry : entity->getComponents()) {
	  if (componentEntry.second->hasFlag(Component::CLIENT_SERIALIZABLE_MASK)) {
	    try {
	      components << componentEntry.second->getType() << componentEntry.second->serialize();
	    }
	    catch (const Component::ComponentFlagException &e) {
	    logs::getLogger()[logs::ERRORS] << e.what() << std::endl;
	    }
	  }
	}
      clientc->_clientUDP->addMessage(protocol::client::entityUpdate(clientc->_clientToken, entity->getId(), components).getBufferString() + network::magic);
      clientc->_clientUDP->update();
      }
    }

    void SysSerialisation::update(WorldData &world) {
      unserialize(world);
      serialize(world, &world._systemEntity);
      for (Entity::Entity *entity : world._gameEntities)
	serialize(world, entity);
    }

    void SysSerialisation::unserialize(WorldData &world) {

      Component::CompNetworkClient *clientc = dynamic_cast<Component::CompNetworkClient*>(world._systemEntity.getComponent(ECS::Component::NETWORK_CLIENT));

      if (clientc && clientc->_clientUDP) {
	try {
	  clientc->_clientUDP->update();
	}
	catch (const network::SocketException &e) {
	  logs::getLogger()[logs::ERRORS] << e.what() << std::endl;
	}
	std::string message;
	while (!(message = clientc->_clientUDP->getMessage()).empty()) {
	  try {
	    bson::Document document(message);
	    if (!protocol::server::checkEntityUpdate(document))
	      logs::getLogger()[logs::ERRORS] << "Invalid packet" << std::endl;
	    else if (document["data"]["token"].getValueString() != clientc->_serverToken)
	      logs::getLogger()[logs::ERRORS] << "Invalid server token" << std::endl;
	    else {
	      Entity::Entity *entity = world.getEntityById(document["data"]["entity_id"].getValueInt64());
	      if (!entity) {
		entity = new Entity::Entity(document["data"]["entity_id"].getValueInt64());
		world._gameEntities.push_back(entity);
	      }
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
		  try {
		    entity->addComponent(builders.at(key)(components[key].getValueDocument()));
		  }
                  catch (const Component::ComponentFlagException &e) {
                    logs::getLogger()[logs::ERRORS] << e.what() << std::endl;
                  }
		  catch (const std::out_of_range &e) {
		    logs::getLogger()[logs::ERRORS] << "Unable to find builders for '" << key << "'" << std::endl;
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
