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
	  std::chrono::high_resolution_clock::time_point start;

	  /**
	   * timestamp of current tick
	   */
	  std::chrono::high_resolution_clock::time_point current;

	  /**
	   * timestamp of previous tick
	   */
	  std::chrono::high_resolution_clock::time_point previous;

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
