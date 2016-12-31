/**
 * @file SysSerialisation.hh
 * @author Nekhot.
 * @brief System for udp networking on client.
 */

#pragma once

#include <string>
#include <unordered_map>
#include <functional>
#include <algorithm>

#include "ECS/World.hh"
#include "ECS/Entity.hh"
#include "ECS/ISystem.hh"
#include "ECS/AComponent.hh"
#include "Logs/Logger.hh"
#include "ECS/AssetLogLevel.hh"
#include "CompNetworkServer.hh"
#include "Network/SocketException.hh"
#include "Protocol/Client.hh"
#include "Protocol/Server.hh"
#include "ECS/CompController.hh"

namespace ECS {
  namespace System {

    /**
     * System for window
     */
    class SysSerialisation : public ISystem {
    public:
      /**
       * Update method
       *
       * @param world All the data about the world
       */
      virtual void update(ECS::WorldData &world);

        /**
         * Serialize the given entity
         *
         * @param world All the data about the world
         * @param entity the entity to serialize
         */
      void serialize(WorldData &world, const Entity::Entity *entity) const;

        /**
         * Unserialize and update the world
         *
         * @param world All the data about the world
         */
      void unserialize(WorldData &world) const;
    };
  }
}
