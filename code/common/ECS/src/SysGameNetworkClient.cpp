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
                if (protocol::server::checkEntityUpdate(doc))
                {
                    logs::logger[logs::ECS] << doc.toJSON() << std::endl;

                    if (Component::CompNetworkClient::isValidActionUdp(doc["header"]["action"].getValueString()))
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
                                    logs::logger[logs::ERRORS] << e.what() << std::endl;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}