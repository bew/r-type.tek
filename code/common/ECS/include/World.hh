
/**
 * @file World.hh
 * @author Alexis
 * @brief This class implement the whole world of the R-Type !
 */

#pragma once

#include "ISystem.hh"
#include "Entity.hh"

#include <vector>


/**
 * Namespace of ECS.
 */
namespace ECS {

    /**
     * Data of the ecs. The systems will read and update these datas.
     */
    struct WorldData
    {
	/**
	 * packets read on the network, waiting to be consumed.
	 */
	std::vector<std::string>	_packetsRead;

	/**
	 * packets to write on the network.
	 */
	std::vector<std::string>	_packetsToWrite;

        /**
	 * Game entities such as enemy, players, or bullets.
	 */
	std::vector<Entity::Entity>	_gameEntities;

        /**
	 * System entity managing network and graphics components.
	 */
	Entity::Entity			_systemEntity;
    };
    
    /**
     * Class containing the ECS.
     */
    class World
    {
    public:
	/**
	 * Constructor.
	 */
	World();

	/**
	 * Destructor.
	 */
	~World();

	World(const World &) = delete;
	World &operator=(const World &) = delete;

	/**
	 * Calculate one frame of the r-type game.
	 */
	void	update();

    private:
	/**
	 * Systems.
	 */
	std::vector<System::ISystem *>	_systems;

        /**
	 * Data of the ecs. The systems will read and update these datas.
	 */
	WorldData			_world;

	/**
	 * Pools of objects used by the ECS.
	 */
	Pools::WorldPools		_pools;
    };

}
