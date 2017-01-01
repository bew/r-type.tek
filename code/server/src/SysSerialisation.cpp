/**
 * @file SysSerialisation.cpp
 * @author Nekhot
 * @brief Impelmentation of system udp packet.
 */

#include "SysSerialisation.hh"
#include "ECS/World.hh"

namespace ECS {
    namespace System {

        void SysSerialisation::serialize(WorldData &world, const Entity::Entity *entity) const {
            Component::CompNetworkServer *serverc = dynamic_cast<Component::CompNetworkServer *>(world._systemEntity.getComponent(ECS::Component::NETWORK_SERVER));
            if (!serverc)
                return;

            bson::Document components;
            for (const auto &componentEntry : entity->getComponents()) {
                if (componentEntry.second->hasFlag(Component::SERVER_SERIALIZABLE_MASK)) {
                    try {
                        if (componentEntry.second->getType() == Component::CONTROLLER &&
                            entity->getId() >= 1 && entity->getId() <= 4 &&
                            entity->getId() <= serverc->_server.getConnections().size()) {
			  bson::Document controller;
                            controller << Component::CONTROLLER << componentEntry.second->serialize();
                            serverc->_server.addMessage
                                    (serverc->_server.getConnections()[entity->getId() - 1],
                                     protocol::client::entityUpdate(serverc->_serverToken, entity->getId(),
                                                                    controller).getBufferString());
                        } else
                            components << componentEntry.second->getType() << componentEntry.second->serialize();
                    }
                    catch (const Component::ComponentFlagException &e) {
                        logs::getLogger()[logs::ERRORS] << e.what() << std::endl;
                    }
                }
            }

            for (auto connected : serverc->_server.getConnections()) {
                bson::Document message = protocol::server::entityUpdate(serverc->_serverToken, entity->getId(), components);
                serverc->_server.addMessage(connected, message.getBufferString());
	        }

            try {
                serverc->_server.update();
            }
            catch (const network::SocketException &e) {
                logs::getLogger()[logs::ERRORS] << e.what() << std::endl;
                return;
            }
        }

        void SysSerialisation::update(WorldData &world) {
            unserialize(world);
            serialize(world, &world._systemEntity);
            for (const Entity::Entity *entity : world._gameEntities)
                serialize(world, entity);
        }

        void SysSerialisation::unserialize(WorldData &world) const {
            Component::CompNetworkServer *serverc = dynamic_cast<Component::CompNetworkServer *>(world._systemEntity.getComponent(ECS::Component::NETWORK_SERVER));
            if (!serverc)
                return;

            std::string message;
            for (const auto &connected : serverc->_server.getConnections()) {
                while (!(message = serverc->_server.getMessage(connected)).empty()) {
                    bson::Document document;
                    try {
                        document = bson::Document(message);
                    }
                    catch (const bson::BsonException &e) {
                        logs::getLogger()[logs::ERRORS] << e.what() << std::endl;
                        return;
                    }
                    if (!protocol::server::checkEntityUpdate(document)) {
                        logs::getLogger()[logs::ERRORS] << "Invalid packet" << std::endl;
                        return;
                    } else if (std::find(serverc->_clientTokens.begin(), serverc->_clientTokens.end(), document["data"]["token"].getValueString()) == serverc->_clientTokens.end()) {
                        logs::getLogger()[logs::ERRORS] << "Invalid client token" << std::endl;
                        return;
                    }

                    int64_t entityId = document["data"]["entity_id"].getValueInt64();
                    Entity::Entity *entity = world.getEntityById(entityId);
                    if (!entity) {
                        logs::getLogger()[logs::ERRORS] << "Client tried to create new entity with id: " << entityId
                                                        << std::endl;
                        return;
                    }

                    const bson::Document &components = document["data"]["components"].getValueDocument();
                    for (const std::string &key : components.getKeys()) {
                        Component::AComponent *component = entity->getComponent(key);
                        if (!component) {
                            logs::getLogger()[logs::ERRORS] << "Client tried to create new component '"
                                                            << key << "'" << std::endl;
                            continue;
                        }
                        try {
                            component->deserialize(components[key].getValueDocument());
                        }
                        catch (const Component::ComponentFlagException &e) {
                            logs::getLogger()[logs::ERRORS] << e.what() << std::endl;
                        }
                    }
                }
            }
        }
    }
}
