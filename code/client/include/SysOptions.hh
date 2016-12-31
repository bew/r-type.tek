/**
 * @file SysOptions.hh
 * @author Nekhot
 * @brief Header of System for emitting event on configuration change.
 */

#pragma once

#include <iterator>
#include <fstream>
#include "ECS/World.hh"
#include "ECS/Entity.hh"
#include "ECS/ISystem.hh"
#include "ECS/CompEvent.hh"
#include "BSON/Document.hh"
#include "CompOptions.hh"
#include "Logs/Logger.hh"

namespace ECS {
  namespace System {

    /**
     * System for Options
     */
    class SysOptions : public ISystem {
    public:

      /**
       * Update method
       *
       * @param world All the data about the world
       */
      virtual void update(ECS::WorldData &world);

      /**
       * The file for serializing/deserializing configuration
       */
      static const std::string CONFIG_FILE;
      
      /**
       * Hook for updating the configuration file
       *
       * @tparam repeat Should the hook persist
       */
      template<bool repeat>
      static bool READ_CONFIG_FILE(ECS::Component::CompEvent::IEvent *event, ECS::WorldData &world) {
	Component::CompOptions *optionsc = dynamic_cast<Component::CompOptions*>(world._systemEntity.getComponent(ECS::Component::OPTIONS));

	logs::getLogger()[logs::INFO] << "Loading configuration file '" << SysOptions::CONFIG_FILE  << "'" << std::endl;
	
	try {
	  bson::Document document;
	  document.readFromFile(SysOptions::CONFIG_FILE, true);
	  optionsc->setLocale(document["locale"].getValueString());
	  optionsc->setMusicVolume(static_cast<float>(document["music"].getValueDouble()));
	  optionsc->setSoundEffectVolume(static_cast<float>(document["effect"].getValueDouble()));
          optionsc->setFullscreen(document["fullscreen"].getValueBool());
          optionsc->setWidth(document["width"].getValueInt64());
          optionsc->setHeight(document["height"].getValueInt64());
          optionsc->setAAliasing(document["aaliasing"].getValueInt64());
          optionsc->setTitle(document["title"].getValueString());	  
	  return repeat;
	}
	catch (const bson::BsonException &e) {
	  logs::getLogger()[logs::ERRORS] << "Cannot load from configuration file (file is corrupted or absent)'" << e.what() << "'" << std::endl;
	  WRITE_CONFIG_FILE<false>(nullptr, world);
	  return repeat;
	}
      }
      
      /**
       * Hook for updating the configuration file
       *
       * @tparam repeat Should the hook persist
       */
      template<bool repeat>
      static bool WRITE_CONFIG_FILE(ECS::Component::CompEvent::IEvent *event, ECS::WorldData &world) {
	Component::CompOptions *optionsc = dynamic_cast<Component::CompOptions*>(world._systemEntity.getComponent(ECS::Component::OPTIONS));

	logs::getLogger()[logs::INFO] << "Updating configuration file '" << SysOptions::CONFIG_FILE  << "'" << std::endl;
	
	try {
	  bson::Document options;
	  if (optionsc) {
	    options << "locale" << optionsc->getLocale();
	    options << "music" << optionsc->getMusicVolume();
	    options << "effect" << optionsc->getSoundEffectVolume();
	    options << "fullscreen" << optionsc->getFullscreen();
	    options << "width" << static_cast<int>(optionsc->getWidth());
	    options << "height" << static_cast<int>(optionsc->getHeight());
	    options << "aaliasing" << static_cast<int>(optionsc->getAAliasing());
	    options << "title" << optionsc->getTitle();
	    options.writeToFile(SysOptions::CONFIG_FILE, true);
	  }
	}
	catch (const bson::BsonException &e) {
          logs::getLogger()[logs::ERRORS] << "Cannot update configuration file '" << e.what() << "'" << std::endl;
          return repeat;
        }
	return repeat;
      }
      
    };
  }
}
