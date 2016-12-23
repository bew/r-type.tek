/**
 * @file SysOptions.hh
 * @author Nekhot
 * @brief Header of System for emitting event on configuration change.
 */

#pragma once

#include <iterator>
#include <fstream>
#include "World.hh"
#include "Entity.hh"
#include "ISystem.hh"
#include "CompEvent.hh"
#include "Document.hh"
#include "CompOptions.hh"
#include "Logger.hh"
#include "Logs/ErrorLogLevel.hh"

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
	std::ifstream file(SysOptions::CONFIG_FILE, std::ios::binary);
	std::streampos fileSize;
	std::vector<unsigned char> buffer;

	if (!file.is_open()) {
	  //logs::logger.logLevel(logs::ERROR) << "Cannot read from configuration file " << SysOptions::CONFIG_FILE << std::endl;
	  return repeat;
	}
	file.unsetf(std::ios::skipws);
	file.seekg(0, std::ios::end);
	fileSize = file.tellg();
	file.seekg(0, std::ios::beg);
	buffer.reserve(static_cast<unsigned int>(fileSize));
	buffer.insert(buffer.begin(),
		      std::istream_iterator<unsigned char>(file),
		      std::istream_iterator<unsigned char>());
	try {
	  const bson::Document document(buffer);
	  optionsc->setLocale(document["locale"].getValueString());
	  optionsc->setMusicVolume(static_cast<float>(document["effect"].getValueDouble()));
	  optionsc->setSoundEffectVolume(static_cast<float>(document["music"].getValueDouble()));
          optionsc->setFullscreen(document["fullscreen"].getValueBool());
          optionsc->setWidth(document["width"].getValueInt32());
          optionsc->setHeight(document["height"].getValueInt32());
          optionsc->setAAliasing(document["aliasing"].getValueInt32());
          optionsc->setTitle(document["title"].getValueString());	  
	  return repeat;
	}
	catch (const bson::BsonException &e) {
	  logs::logger.logLevel(logs::ERROR) << "Cannot parse from configuration file '" << e.what() << "'" << std::endl;
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
	std::ofstream file(SysOptions::CONFIG_FILE, std::ios::binary);
	if (!file.is_open()) {
	  logs::logger.logLevel(logs::ERROR) << "Cannot write to configuration file " << SysOptions::CONFIG_FILE << std::endl;
	  return repeat;
	}
	bson::Document options;
	if (optionsc && file.is_open()) {
	  options << "locale" << optionsc->getLocale();
	  options << "effect" << optionsc->getMusicVolume();
	  options << "music" << optionsc->getSoundEffectVolume();
	  options << "fullscreen" << optionsc->getFullscreen();
	  options << "width" << static_cast<int>(optionsc->getWidth());
	  options << "height" << static_cast<int>(optionsc->getHeight());
	  options << "aaliasing" << static_cast<int>(optionsc->getAAliasing());
	  options << "title" << optionsc->getTitle();
	  file.write(reinterpret_cast<char*>(&(options.getBuffer()[0])), options.getBuffer().size());
	}
	return repeat;
      }
      
    };
  }
}
