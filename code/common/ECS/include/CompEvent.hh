/**
 * @file CompEvent.hh
 * @author Nekhot.
 * @brief Header for component events.
 *
 */

#pragma once

#include <unordered_map>
#include <functional>

#include "AComponent.hh"

/**
 * Namespace of ECS.
 */
namespace ECS {

    /**
     * Namespace of components.
     */
    namespace Component {
      
      /**
       * Component to hold events
       */
      class CompEvent : public AComponent {
      public:
	
	/**
	 * Events interface
	 */
	class IEvent {
	public:
	  virtual ~IEvent(void);
	};

	/**
	 * Default constructor
	 */
	CompEvent(void);
	
	/**
	 * The hooks, functor to call when an event with the key as a name is emitted
	 */
	std::unordered_multimap<std::string, std::function<bool(IEvent *)>> _hooks;
	
	/**
	 * The event that have been emitted, and that need to be consummed
	 */
	std::unordered_multimap<std::string, IEvent *> _events;
      };
    }
}
