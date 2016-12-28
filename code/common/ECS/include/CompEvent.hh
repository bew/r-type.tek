/**
 * @file CompEvent.hh
 * @author Nekhot.
 * @brief Header for component events.
 */

#pragma once

#include <unordered_map>
#include <functional>

#include "World.hh"
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
        static const std::string EVENT = "event";

        /**
         * Component to hold events
         */
        class CompEvent : public AComponent
        {
        public:

	  /**
	   * Events interface
	   */
	  class IEvent
	  {
	  public:
	    virtual ~IEvent(void);
	  };

	  /**
	   * An event handler.
	   */
	  typedef std::function<bool(IEvent *, WorldData &)> EventHandler;

	  /**
	   * Default constructor
	   */
	  CompEvent(void);

	  /**
	   * The hooks, functor to call when an event with the key as a name is emitted.
	   */
	  std::unordered_multimap<std::string, EventHandler> _hooks;

	  /**
	   * The event that have been emitted, and that need to be consummed.
	   *
	   * If an events is added in this container while event are being processed, there will be no garantee
	   * about in which tick it will be executed (current or next).
	   * Consider not adding event in it when event are being processed.
	   */
	  std::unordered_multimap<std::string, IEvent *> _events;

	  /**
	   * The event that have been emitted while prcessing event, and that need to be processed in the same tick they have been emitted.
	   * PLEASE NOTE that if misused (like emtting circular event), this while indefinitely block the current tick, or may cause it to took
	   * a lot of time to process. You should not use this if you don't know exactly wht you are doing.
	   *
	   * Use case are event that should be very quick, but doesn't throw other event
	   */
	  std::unordered_multimap<std::string, IEvent *> _sameTickEvents;

	  /**
	   * The event that have been emitted, while processign event.
	   *
	   * They will be processed the during ths tick following the one they have been emitted from.
	   */
	  std::unordered_multimap<std::string, IEvent *> _nextTickEvents;

	  /**
	   * Specify if the event is currently being processed.
	   */
	  bool locked;

	  /**
	   * Add a hook for eventName.
	   * There may be multiple hook for the same eventName
	   *
	   * @param eventName The name of the event that will fire the function
	   * @param hook The function to be called. The function will be passed a MAYBE NULL pointer to IEvent.
	   *             If this function return false, the hook will be removed from the map.
	   */
	  void addHook(const std::string &eventName, EventHandler hook);

	  /**
	   * Add a hook for eventName.
	   * There may be multiple event for the same eventName
	   * This event will always be processed in the NEXT event processing loop.
	   *  This mean that if used before event processing loop, the event will be processed in current tick.
	   *                 else it will be processed in NEXT tick.
	   *
	   * @param eventName The name of the event that will fire the function
	   * @param event The event passed to hooks for eventName, if there are some
	   */
	  void addEvent(const std::string &eventName, IEvent *event = nullptr);

	  /**
	   * Add a hook for eventName.
	   * There may be multiple event for the same eventName
	   * This event will always be processed in the SAME tick.
	   * This should not be used out of event handler.
	   * This should NEVER be called "recusively", and actually should be used if you don't knwo
	   *    exactly what you are doing. See _sameTickevents
	   *
	   * @param eventName The name of the event that will fire the function
	   * @param event The event passed to hooks for eventName, if there are some
	   */
	  void addSameTickEvent(const std::string &eventName, IEvent *event = nullptr);

	  /**
	   * get the type of component
	   * @return string that reprents his type
	   */
	  virtual const std::string& getType() const;
        };
    }
}
