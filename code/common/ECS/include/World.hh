
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
	 * Constructor.
	 */
	WorldData();
	
	/**
	 * Destructor.
	 */
	~WorldData();

        /**
	 * Game entities such as enemy, players, or bullets.
	 */
	std::vector<Entity::Entity *>	_gameEntities;

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
	
	/**
	 * Initiate the systems of the world.
	 */
	void	initTestSystem();

	/**
	 * Add a test entity in the world.
	 */
	void	addTestEntity();

	/**
	 * Add a system in the world.
	 * @param system The system to be added.
	 */
	void	World::addSystem(System::ISystem *system)

    private:
	/**
	 * Systems.
	 */
	std::vector<System::ISystem *>	_systems;

        /**
	 * Data of the ecs. The systems will read and update these datas.
	 */
	WorldData			_world;
    };

}
