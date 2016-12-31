/**
 * @file SysSerialisation.cpp
 * @author Nekhot
 * @brief Impelmentation of system udp packet.
 */

#include "SysSerialisation.hh"

namespace ECS {
  namespace System {

    void SysSerialisation::serialize(WorldData &world, Entity::Entity *entity) {
      Component::CompNetworkClient *clientc = dynamic_cast<Component::CompNetworkClient*>(world._systemEntity.getComponent(ECS::Component::NETWORK_CLIENT));

      bson::Document components;
      if (clientc)
	for (auto componentEntry : entity.getComponents()) {
	  if (componentEntry.second->hasFlag(CLIENT_SERIALIZABLE_MASK)) {
	    try {
	      //blalba
	    }
	    catch (const Component::ComponentFlagException &e) {
	    logs::getLogger()[logs::ERRORS] << e.what() << std::endl;
	    }
	  }
	}
      
      clientc->_clientUDP.addMessage(protocol::client::entityUpdate("bite poile chatte", entity->getId(), components).getBufferString() + network::magic);
      clientc->_clientUDP.update();
    }

    void SysSerialisation::update(WorldData &world) {

      Component::CompNetworkClient *clientc = dynamic_cast<Component::CompNetworkClient*>(world._systemEntity.getComponent(ECS::Component::NETWORK_CLIENT));
      
      if (clientc) {
	try {
	  clientc->_clientUDP.update();
	}
	catch (const network::SocketException &e) {
	  logs::getLogger()[logs::ERRORS] << e.what() << std::endl;
	}
	std::string message;
	while (!(message = clientc->_clientUDP.getMessage()).empty()) {
	  try {
	    bson::Document document(message);
	    Entity::Entity *entity = world.getEntityById(document["data"]["entity_id"].getValueInt64());
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
	    }
	  }
	  catch (const bson::BsonException &e) {
	    logs::getLogger()[logs::ERRORS] << e.what() << std::endl;
	  }
	}
      }
    }
    serialize(world, &world._systemEntity);
    for (Entity::Entity *entity : world._gameEntities)
      serilize(world, entity);
  }
}
