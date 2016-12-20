/**
 * @file libraryUtils.hh
 * @brief Utils macro for easy writin generator, and Header for said Generator 
 * @author Nekhot
 */

#pragma once

#include <type_traits>
#include <string>
#include <vector>

#include "ALibraryLoader.hh"

/**
 * Placeholder class for entity
 */
class Entity {};

/**
 * Placeholder class for storing game status
 */
class EngineStatus {
  /*
    TO UPDATE
    Hold informations like time since begining of level,
    choosen difficulty (idk)
    frame counter,
    maybe the server log ... things like that
  */
};

/**
 * Base interface from which every dynamically loaded class must inherit
 *
 * THS NEED TO BE REFACTORED, DO NOT USE YET
 */
class IGenerator {
public:
  IGenerator(void) {};
  virtual ~IGenerator(void) {};
  
  /**
   * Method to access the name of the generator.
   *
   * @return The name of the generator.
   */
  virtual const std::string &getName(void) const = 0;
  
  /**
   * This take the current entity, and return a list of new entity to add.
   * The pupose is to generate a whole level. It should be called each n frame. 
   * It should not add or edit player entity.
   *
   * @return Vector of new entity to add
   * @param entities Vector of current entiter
   */
  virtual std::vector<Entity>process(std::vector<Entity> &entities, EngineStatus &) = 0;
};

/**
 * What does it do:
 * STRING(test) => "test"
 * define ANOTHER_MACRO test
 * STRING(ANOTHER_MACRO) => "ANOTHER_MACRO"
 */
#define STRING(s) #s

/**
 * What does it do:
 * define ANOTHER_MACRO test
 * EXPAND_STRING(ANOTHER_MACRO) => "test"
 */
#define EXPAND_STRING(s) STRING(s)


/**
 * The name of the exported symbols
 */
#define EXPORT_SYMBOL_NAME export_library_factory

/**
 * Usefull for code factorisation issue.
 * See macro EXPORT
 */
#ifdef _WIN32
    #define EXPORT_DECORATOR __declspec(dllexport)
#elif defined __linux__
    #define EXPORT_DECORATOR
#endif

/**
 * Macro for exporting the dynamically loaded class, to add in the library implementation once.
 *
 * Exemple:
 *  class libhello : public IGenerator {...};
 *  EXPORT(libhello);
 *
 *  Target must have a default constructor.
 */
#define EXPORT(TARGET)                                                                      \
extern "C" {                                                                                \
  EXPORT_DECORATOR IGenerator *EXPORT_SYMBOL_NAME(void) {				    \
    static_assert(std::is_default_constructible<TARGET>::value,				    \
      "Exported type must have a public default constructor");				    \
    return new TARGET();  								    \
  }                                                                                         \
}
