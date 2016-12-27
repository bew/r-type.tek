/**
 * @file SysGameNetworkClient.cpp
 * @author Tookie.
 * @brief System for client network during a game.
 */

#include <ECSLogLevel.hh>
#include "SysGameNetworkClient.hh"
#include "CompNetworkClient.hh"
#include "Protocol/Server.hh"

namespace ECS
{
    namespace System
    {
        void SysGameNetworkClient::update(ECS::WorldData &world)
        {
            Component::CompNetworkClient *network = dynamic_cast<Component::CompNetworkClient *> (world._systemEntity.getComponent(
                Component::NETWORK_CLIENT));

            if (network)
            {
                network->_clientUDP.update();
                bson::Document doc(network->_clientUDP.getMessage());
                if (!doc.isEmpty() && protocol::server::checkEntityUpdate(doc))
                {
                    logs::logger[logs::ECS] << doc.toJSON() << std::endl;

                    Entity::Entity *entity = world.getEntityById(doc["data"]["entity_id"].getValueInt64());

                    bson::Document components = doc["data"]["components"].getValueDocument();

                    for (const auto& keys : components.getKeys())
                    {
                        Component::AComponent *component = entity->getComponent(keys);
                        if (component)
                        {
                            try
                            {
                                component->deserialize(components[keys].getValueDocument());
                            }
                            catch (Component::ComponentFlagException &e)
                            {
                                logs::logger[logs::ERRORS] << e.what() << std::endl;
                            }
                        }
                    }
                }
            }
        }
    }
}