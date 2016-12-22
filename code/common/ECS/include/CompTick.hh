/**
 * @file CompTick.hh
 * @author Nekhot
 * @brief Header for component tick
 */

#pragma once

#include <chrono>
#include <ratio>

#include "AComponent.hh"

/**
 * Namespace of ECS.
 */
namespace ECS
{

    /**
     * Namespace of components.
     */
    namespace Component
    {
        /**
         * Component type id.
         */
        static const std::string TICK = "tick";

        /**
         * Component to hold track of ticks
         */
        class CompTick : public AComponent
        {
        public:

	  /**
	   * Default frequency
	   */
	  static const unsigned int FREQUENCY;
	  
	  /**
	   * Default constructor
	   */
	  CompTick(void);

	  /**
	   * Tick count
	   */
	  int tick;

	  /**
	   * frequency (allowed tick per second)
	   */
	  std::chrono::duration<float, std::ratio<1>> tickDuration;

	  /**
	   * Mean lag
	   */
	  std::chrono::nanoseconds lag;

	  /**
	   * timestamp of first tick
	   */
	  std::chrono::time_point<std::chrono::system_clock> start;

	  /**
	   * timestamp of current tick
	   */
	  std::chrono::time_point<std::chrono::system_clock> current;

	  /**
	   * timestamp of previous tick
	   */
	  std::chrono::time_point<std::chrono::system_clock> previous;

	  /**
	   * Set to true to kill the game
	   */
	  bool kill;

	  /**
	   * Get the component type
	   *
	   * @return ECS::Component::TICK
	   */
	  virtual const std::string& getType() const;
        };
    }
}
