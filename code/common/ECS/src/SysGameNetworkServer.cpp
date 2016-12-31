/**
 * @file SysGameNetworkServer.cpp
 * @author Tookie.
 * @brief System for server network during a game.
 */

#include "CompNetworkServer.hh"
#include "SysGameNetworkServer.hh"
#include "Protocol/Client.hh"
#include "ECSLogLevel.hh"


namespace ECS
{
    namespace System
    {

        void SysGameNetworkServer::update(ECS::WorldData &world)
        {
            Component::CompNetworkServer *network = dynamic_cast<Component::CompNetworkServer *> (world._systemEntity.getComponent(
                Component::NETWORK_SERVER));

            if (network)
            {
                network->_server.update();
                for (auto &client: network->_server.getConnections())
                {
                    if (!client->hasMessage())
                        continue;
                    bson::Document doc(network->_server.getMessage(client));
                    if (protocol::client::checkEntityUpdate(doc))
                    {
                        logs::getLogger()[logs::ECS] << doc.toJSON() << std::endl;

                        if (Component::CompNetworkServer::isValidActionUdp(doc["header"]["action"].getValueString()))
                        {
                            Entity::Entity *entity = world.getEntityById(doc["data"]["entity_id"].getValueInt64());

                            const bson::Document &components = doc["data"]["components"].getValueDocument();

                            for (const std::string &key : components.getKeys())
                            {
                                Component::AComponent *component = entity->getComponent(key);
                                if (component)
                                {
                                    try
                                    {
                                        component->deserialize(components[key].getValueDocument());
                                    }
                                    catch (Component::ComponentFlagException &e)
                                    {
                                        logs::getLogger()[logs::ERRORS] << e.what() << std::endl;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}