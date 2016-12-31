/**
 * @file SysSerialisation.hh
 * @author Nekhot.
 * @brief System for udp networking on client.
 */

#pragma once

#include <string>

#include "ECS/World.hh"
#include "ECS/Entity.hh"
#include "ECS/ISystem.hh"
#include "ECS/AComponent.hh"
#include "Logs/Logger.hh"
#include "ECS/AssetLogLevel.hh"
#include "CompNetworkClient.hh"
#include "Network/SocketException.hh"

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
    };
  }
}
